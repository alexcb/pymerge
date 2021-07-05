#include <Python.h>
#include <stdio.h>

#include "merge.h"

PyObject* merge( PyObject* self, PyObject* args )
{
	int i;
	int n1, n2;
	int i1 = 0, i2 = 0;
	int result;

	PyObject* listObj1 = NULL;
	PyObject* listObj2 = NULL;
	PyObject* elem1 = NULL;
	PyObject* elem2 = NULL;

	if( !PyArg_ParseTuple( args, "O!O!", &PyList_Type, &listObj1, &PyList_Type, &listObj2 ) )
		return NULL;

	n1 = PyList_Size( listObj1 );
	n2 = PyList_Size( listObj2 );

	/* TODO check where reference counting is required */
	PyObject* mergedList = PyList_New( n1 + n2 );

	/* should raise an error here. */
	if( n1 < 0 || n2 < 0 )
		return NULL; /* Not a list */

	for( i = 0;; ) {
		if( i1 < n1 ) {
			if( !elem1) {
				elem1 = PyList_GetItem( listObj1, i1 );
			}
			if( i2 < n2 ) {
				if( !elem2 ) {
					elem2 = PyList_GetItem( listObj2, i2 );
				}
				// PyObject_RichCompareBool appears to be stealing the reference
				Py_INCREF( elem1 );
				Py_INCREF( elem2 );
				result = PyObject_RichCompareBool( elem1, elem2, Py_LE );
				switch( result ) {
				case 1:
					PyList_SetItem( mergedList, i++, elem1 );
					elem1 = NULL;
					i1++;
					break;

				case 0:
					PyList_SetItem( mergedList, i++, elem2 );
					elem2 = NULL;
					i2++;
					break;

				default:
					// error occured
					return NULL; /* TODO should raise an error */
				}
			}
			else {
				PyList_SetItem( mergedList, i++, elem1 );
				elem1 = NULL;
				i1++;
			}
		}
		else {
			if( i2 < n2 ) {
				elem2 = PyList_GetItem( listObj2, i2 );
				PyList_SetItem( mergedList, i++, elem2 );
				elem2 = NULL;
				i2++;
			}
			else {
				break;
			}
		}
	}

	Py_DECREF( listObj1 );
	Py_DECREF( listObj2 );

	return mergedList;
}
