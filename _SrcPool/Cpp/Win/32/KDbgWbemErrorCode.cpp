/*$RCSfile: KDbgWbemErrorCode.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/02/03 22:10:50 $
  $Author: ddarko $

  Dumps Web-Based Enterprise Management (WBEM) error descriptions
  Copyright: Darko Kolakovic
  Darko Kolakovic 2010-01-15
 */

// Group=Diagnostic

#include "stdafx.h"
#include <wbemidl.h> //Web-based Enterprise Management (WBEM) status codes

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Dumps the Web-Based Enterprise Management (WBEM) error messages. 
  These error codes are defined in wbemcli.h.

  WBEM is a set of systems management technologies developed to unify the 
  management of distributed computing environments.

  Note: Microsoft Windows specific (Win2k).
 */
LPCTSTR DumpWbemErrorCode(const HRESULT hWmiError, //[in] WBEM error code
                          LPCTSTR* pszDescription  //[out] long description of the 
                          //WBEM error, unless the parameter is NULL.
                          )
{
LPCTSTR szCode = NULL;
LPCTSTR szDescription = NULL;
switch(hWmiError)
  {
  case WBEM_E_FAILED: //0x80041001
     szCode = _T("WBEM_E_FAILED");                              szDescription = _T("Call failed");break;
  case WBEM_E_NOT_FOUND: //0x80041002
     szCode = _T("WBEM_E_NOT_FOUND");                           szDescription = _T("Object cannot be found");break;
  case WBEM_E_ACCESS_DENIED: //0x80041003
     szCode = _T("WBEM_E_ACCESS_DENIED");                       szDescription = _T("Current user does not have permission to perform the action");break;
  case WBEM_E_PROVIDER_FAILURE: //0x80041004
     szCode = _T("WBEM_E_PROVIDER_FAILURE");                    szDescription = _T("Provider has failed at some time other than during initialization");break;
  case WBEM_E_TYPE_MISMATCH: //0x80041005
     szCode = _T("WBEM_E_TYPE_MISMATCH");                       szDescription = _T("Type mismatch occurred");break;
  case WBEM_E_OUT_OF_MEMORY: //0x80041006
     szCode = _T("WBEM_E_OUT_OF_MEMORY");                       szDescription = _T("Not enough memory for the operation");break;
  case WBEM_E_INVALID_CONTEXT: //0x80041007
     szCode = _T("WBEM_E_INVALID_CONTEXT");                     szDescription = _T("The IWbemContext object is not valid");break;
  case WBEM_E_INVALID_PARAMETER: //0x80041008
     szCode = _T("WBEM_E_INVALID_PARAMETER");                   szDescription = _T("One of the parameters to the call is not correct");break;
  case WBEM_E_NOT_AVAILABLE: //0x80041009
     szCode = _T("WBEM_E_NOT_AVAILABLE");                       szDescription = _T("Resource typically a remote server is not currently available");break;
  case WBEM_E_CRITICAL_ERROR: //0x8004100A
     szCode = _T("WBEM_E_CRITICAL_ERROR");                      szDescription = _T("Internal critical and unexpected error occurred.");break;
  case WBEM_E_INVALID_STREAM: //0x8004100B
     szCode = _T("WBEM_E_INVALID_STREAM");                      szDescription = _T("One or more network packets were corrupted during a remote session");break;
  case WBEM_E_NOT_SUPPORTED: //0x8004100C
     szCode = _T("WBEM_E_NOT_SUPPORTED");                       szDescription = _T("Feature or operation is not supported");break;
  case WBEM_E_INVALID_SUPERCLASS: //0x8004100D
     szCode = _T("WBEM_E_INVALID_SUPERCLASS");                  szDescription = _T("Parent class specified is not valid");break;
  case WBEM_E_INVALID_NAMESPACE: //0x8004100E
     szCode = _T("WBEM_E_INVALID_NAMESPACE");                   szDescription = _T("Namespace specified cannot be found");break;
  case WBEM_E_INVALID_OBJECT: //0x8004100F
     szCode = _T("WBEM_E_INVALID_OBJECT");                      szDescription = _T("Specified instance is not valid");break;
  case WBEM_E_INVALID_CLASS: //0x80041010
     szCode = _T("WBEM_E_INVALID_CLASS");                       szDescription = _T("Specified class is not valid");break;
  case WBEM_E_PROVIDER_NOT_FOUND: //0x80041011
     szCode = _T("WBEM_E_PROVIDER_NOT_FOUND");                  szDescription = _T("Provider referenced in the schema does not have a corresponding registration");break;
  case WBEM_E_INVALID_PROVIDER_REGISTRATION: //0x80041012
     szCode = _T("WBEM_E_INVALID_PROVIDER_REGISTRATION");       szDescription = _T("Provider referenced in the schema has an incorrect or incomplete registration");break;
  case WBEM_E_PROVIDER_LOAD_FAILURE: //0x80041013
     szCode = _T("WBEM_E_PROVIDER_LOAD_FAILURE");               szDescription = _T("COM cannot locate a provider referenced in the schema");break;
  case WBEM_E_INITIALIZATION_FAILURE: //0x80041014
     szCode = _T("WBEM_E_INITIALIZATION_FAILURE");              szDescription = _T("Component such as a provider failed to initialize for internal reasons");break;
  case WBEM_E_TRANSPORT_FAILURE: //0x80041015
     szCode = _T("WBEM_E_TRANSPORT_FAILURE");                   szDescription = _T("Networking error that prevents normal operation has occurred");break;
  case WBEM_E_INVALID_OPERATION: //0x80041016
     szCode = _T("WBEM_E_INVALID_OPERATION");                   szDescription = _T("Requested operation is not valid. This error usually applies to invalid attempts to delete classes or properties");break;
  case WBEM_E_INVALID_QUERY: //0x80041017
     szCode = _T("WBEM_E_INVALID_QUERY");                       szDescription = _T("Query was not syntactically valid");break;
  case WBEM_E_INVALID_QUERY_TYPE: //0x80041018
     szCode = _T("WBEM_E_INVALID_QUERY_TYPE");                  szDescription = _T("Requested query language is not supported");break;
  case WBEM_E_ALREADY_EXISTS: //0x80041019
     szCode = _T("WBEM_E_ALREADY_EXISTS");                      szDescription = _T("In a put operation the wbemChangeFlagCreateOnly flag was specified but the instance already exists");break;
  case WBEM_E_OVERRIDE_NOT_ALLOWED: //0x8004101A
     szCode = _T("WBEM_E_OVERRIDE_NOT_ALLOWED");                szDescription = _T("Not possible to perform the add operation on this qualifier because the owning object does not permit overrides");break;
  case WBEM_E_PROPAGATED_QUALIFIER: //0x8004101B
     szCode = _T("WBEM_E_PROPAGATED_QUALIFIER");                szDescription = _T("User attempted to delete a qualifier that was not owned. The qualifier was inherited from a parent class");break;
  case WBEM_E_PROPAGATED_PROPERTY: //0x8004101C
     szCode = _T("WBEM_E_PROPAGATED_PROPERTY");                 szDescription = _T("User attempted to delete a property that was not owned. The property was inherited from a parent class");break;
  case WBEM_E_UNEXPECTED: //0x8004101D
     szCode = _T("WBEM_E_UNEXPECTED");                          szDescription = _T("Client made an unexpected and illegal sequence of calls such as calling EndEnumeration before calling BeginEnumeration");break;
  case WBEM_E_ILLEGAL_OPERATION: //0x8004101E
     szCode = _T("WBEM_E_ILLEGAL_OPERATION");                   szDescription = _T("User requested an illegal operation such as spawning a class from an instance");break;
  case WBEM_E_CANNOT_BE_KEY: //0x8004101F
     szCode = _T("WBEM_E_CANNOT_BE_KEY");                       szDescription = _T("Illegal attempt to specify a key qualifier on a property that cannot be a key");break;
  case WBEM_E_INCOMPLETE_CLASS: //0x80041020
     szCode = _T("WBEM_E_INCOMPLETE_CLASS");                    szDescription = _T("Current object is not a valid class definition. Either it is incomplete or it has not been registered");break;
  case WBEM_E_INVALID_SYNTAX: //0x80041021
     szCode = _T("WBEM_E_INVALID_SYNTAX");                      szDescription = _T("Query is syntactically invalid");break;
  case WBEM_E_NONDECORATED_OBJECT: //0x80041022
     szCode = _T("WBEM_E_NONDECORATED_OBJECT");                 szDescription = _T("Reserved for future use");break;
  case WBEM_E_READ_ONLY: //0x80041023
     szCode = _T("WBEM_E_READ_ONLY");                           szDescription = _T("An attempt was made to modify a read-only property");break;
  case WBEM_E_PROVIDER_NOT_CAPABLE: //0x80041024
     szCode = _T("WBEM_E_PROVIDER_NOT_CAPABLE");                szDescription = _T("Provider cannot perform the requested operation");break;
  case WBEM_E_CLASS_HAS_CHILDREN: //0x80041025
     szCode = _T("WBEM_E_CLASS_HAS_CHILDREN");                  szDescription = _T("Attempt was made to make a change that invalidates a subclass");break;
  case WBEM_E_CLASS_HAS_INSTANCES: //0x80041026
     szCode = _T("WBEM_E_CLASS_HAS_INSTANCES");                 szDescription = _T("Attempt was made to delete or modify a class that has instances");break;
  case WBEM_E_QUERY_NOT_IMPLEMENTED: //0x80041027
     szCode = _T("WBEM_E_QUERY_NOT_IMPLEMENTED");               szDescription = _T("Reserved for future use");break;
  case WBEM_E_ILLEGAL_NULL: //0x80041028
     szCode = _T("WBEM_E_ILLEGAL_NULL");                        szDescription = _T("Value of Nothing/NULL was specified for a property that must have a value");break;
  case WBEM_E_INVALID_QUALIFIER_TYPE: //0x80041029
     szCode = _T("WBEM_E_INVALID_QUALIFIER_TYPE");              szDescription = _T("Variant value for a qualifier was provided that is not a legal qualifier type");break;
  case WBEM_E_INVALID_PROPERTY_TYPE: //0x8004102A
     szCode = _T("WBEM_E_INVALID_PROPERTY_TYPE");               szDescription = _T("CIM type specified for a property is not valid");break;
  case WBEM_E_VALUE_OUT_OF_RANGE: //0x8004102B
     szCode = _T("WBEM_E_VALUE_OUT_OF_RANGE");                  szDescription = _T("Request was made with an out-of-range value or it is incompatible with the type");break;
  case WBEM_E_CANNOT_BE_SINGLETON: //0x8004102C
     szCode = _T("WBEM_E_CANNOT_BE_SINGLETON");                 szDescription = _T("Illegal attempt was made to make a class singleton such as when the class is derived from a non-singleton class");break;
  case WBEM_E_INVALID_CIM_TYPE: //0x8004102D
     szCode = _T("WBEM_E_INVALID_CIM_TYPE");                    szDescription = _T("CIM type specified is invalid");break;
  case WBEM_E_INVALID_METHOD: //0x8004102E
     szCode = _T("WBEM_E_INVALID_METHOD");                      szDescription = _T("Requested method is not available");break;
  case WBEM_E_INVALID_METHOD_PARAMETERS: //0x8004102F
     szCode = _T("WBEM_E_INVALID_METHOD_PARAMETERS");           szDescription = _T("Parameters provided for the method are invalid");break;
  case WBEM_E_SYSTEM_PROPERTY: //0x80041030
     szCode = _T("WBEM_E_SYSTEM_PROPERTY");                     szDescription = _T("There was an attempt to get qualifiers on a system property");break;
  case WBEM_E_INVALID_PROPERTY: //0x80041031
     szCode = _T("WBEM_E_INVALID_PROPERTY");                    szDescription = _T("Property type is not recognized");break;
  case WBEM_E_CALL_CANCELLED: //0x80041032
     szCode = _T("WBEM_E_CALL_CANCELLED");                      szDescription = _T("Asynchronous process has been canceled");break;
  case WBEM_E_SHUTTING_DOWN: //0x80041033
     szCode = _T("WBEM_E_SHUTTING_DOWN");                       szDescription = _T("User has requested an operation while WMI is in the process of shutting down");break;
  case WBEM_E_PROPAGATED_METHOD: //0x80041034
     szCode = _T("WBEM_E_PROPAGATED_METHOD");                   szDescription = _T("Attempt was made to reuse an existing method name from a parent class and the signatures do not match");break;
  case WBEM_E_UNSUPPORTED_PARAMETER: //0x80041035
     szCode = _T("WBEM_E_UNSUPPORTED_PARAMETER");               szDescription = _T("One or more parameter values such as a query text is too complex or unsupported");break;
  case WBEM_E_MISSING_PARAMETER_ID: //0x80041036
     szCode = _T("WBEM_E_MISSING_PARAMETER_ID");                szDescription = _T("Parameter was missing from the method call");break;
  case WBEM_E_INVALID_PARAMETER_ID: //0x80041037
     szCode = _T("WBEM_E_INVALID_PARAMETER_ID");                szDescription = _T("Method parameter has an invalid ID qualifier");break;
  case WBEM_E_NONCONSECUTIVE_PARAMETER_IDS: //0x80041038
     szCode = _T("WBEM_E_NONCONSECUTIVE_PARAMETER_IDS");        szDescription = _T("One or more of the method parameters have ID qualifiers that are out of sequence");break;
  case WBEM_E_PARAMETER_ID_ON_RETVAL: //0x80041039
     szCode = _T("WBEM_E_PARAMETER_ID_ON_RETVAL");              szDescription = _T("Return value for a method has an ID qualifier");break;
  case WBEM_E_INVALID_OBJECT_PATH: //0x8004103A
     szCode = _T("WBEM_E_INVALID_OBJECT_PATH");                 szDescription = _T("Specified object path was invalid");break;
  case WBEM_E_OUT_OF_DISK_SPACE: //0x8004103B
     szCode = _T("WBEM_E_OUT_OF_DISK_SPACE");                   szDescription = _T("Disk is out of space or the 4 GB limit on WMI repository (WMI repository) size is reached");break;
  case WBEM_E_BUFFER_TOO_SMALL: //0x8004103C
     szCode = _T("WBEM_E_BUFFER_TOO_SMALL");                    szDescription = _T("Supplied buffer was too small to hold all of the objects in the enumerator or to read a string property");break;
  case WBEM_E_UNSUPPORTED_PUT_EXTENSION: //0x8004103D
     szCode = _T("WBEM_E_UNSUPPORTED_PUT_EXTENSION");           szDescription = _T("Provider does not support the requested put operation");break;
  case WBEM_E_UNKNOWN_OBJECT_TYPE: //0x8004103E
     szCode = _T("WBEM_E_UNKNOWN_OBJECT_TYPE");                 szDescription = _T("Object with an incorrect type or version was encountered during marshaling");break;
  case WBEM_E_UNKNOWN_PACKET_TYPE: //0x8004103F
     szCode = _T("WBEM_E_UNKNOWN_PACKET_TYPE");                 szDescription = _T("Packet with an incorrect type or version was encountered during marshaling");break;
  case WBEM_E_MARSHAL_VERSION_MISMATCH: //0x80041040
     szCode = _T("WBEM_E_MARSHAL_VERSION_MISMATCH");            szDescription = _T("Packet has an unsupported version");break;
  case WBEM_E_MARSHAL_INVALID_SIGNATURE: //0x80041041
     szCode = _T("WBEM_E_MARSHAL_INVALID_SIGNATURE");           szDescription = _T("Packet appears to be corrupt");break;
  case WBEM_E_INVALID_QUALIFIER: //0x80041042
     szCode = _T("WBEM_E_INVALID_QUALIFIER");                   szDescription = _T("Attempt was made to mismatch qualifiers such as putting [key] on an object instead of a property");break;
  case WBEM_E_INVALID_DUPLICATE_PARAMETER: //0x80041043
     szCode = _T("WBEM_E_INVALID_DUPLICATE_PARAMETER");         szDescription = _T("Duplicate parameter was declared in a CIM method");break;
  case WBEM_E_TOO_MUCH_DATA: //0x80041044
     szCode = _T("WBEM_E_TOO_MUCH_DATA");                       szDescription = _T("Reserved for future use");break;
  case WBEM_E_SERVER_TOO_BUSY: //0x80041045
     szCode = _T("WBEM_E_SERVER_TOO_BUSY");                     szDescription = _T("Call to IWbemObjectSink::Indicate has failed. The provider can refire the event");break;
  case WBEM_E_INVALID_FLAVOR: //0x80041046
     szCode = _T("WBEM_E_INVALID_FLAVOR");                      szDescription = _T("Specified qualifier flavor was invalid");break;
  case WBEM_E_CIRCULAR_REFERENCE: //0x80041047
     szCode = _T("WBEM_E_CIRCULAR_REFERENCE");                  szDescription = _T("Attempt was made to create a reference that is circular (for example deriving a class from itself)");break;
  case WBEM_E_UNSUPPORTED_CLASS_UPDATE: //0x80041048
     szCode = _T("WBEM_E_UNSUPPORTED_CLASS_UPDATE");            szDescription = _T("Specified class is not supported");break;
  case WBEM_E_CANNOT_CHANGE_KEY_INHERITANCE: //0x80041049
     szCode = _T("WBEM_E_CANNOT_CHANGE_KEY_INHERITANCE");       szDescription = _T("Attempt was made to change a key when instances or subclasses are already using the key");break;
  case WBEM_E_CANNOT_CHANGE_INDEX_INHERITANCE: //0x80041050
     szCode = _T("WBEM_E_CANNOT_CHANGE_INDEX_INHERITANCE");     szDescription = _T("An attempt was made to change an index when instances or subclasses are already using the index");break;
  case WBEM_E_TOO_MANY_PROPERTIES: //0x80041051
     szCode = _T("WBEM_E_TOO_MANY_PROPERTIES");                 szDescription = _T("Attempt was made to create more properties than the current version of the class supports");break;
  case WBEM_E_UPDATE_TYPE_MISMATCH: //0x80041052
     szCode = _T("WBEM_E_UPDATE_TYPE_MISMATCH");                szDescription = _T("Property was redefined with a conflicting type in a derived class");break;
  case WBEM_E_UPDATE_OVERRIDE_NOT_ALLOWED: //0x80041053
     szCode = _T("WBEM_E_UPDATE_OVERRIDE_NOT_ALLOWED");         szDescription = _T("Attempt was made in a derived class to override a qualifier that cannot be overridden");break;
  case WBEM_E_UPDATE_PROPAGATED_METHOD: //0x80041054
     szCode = _T("WBEM_E_UPDATE_PROPAGATED_METHOD");            szDescription = _T("Method was re-declared with a conflicting signature in a derived class");break;
  case WBEM_E_METHOD_NOT_IMPLEMENTED: //0x80041055
     szCode = _T("WBEM_E_METHOD_NOT_IMPLEMENTED");              szDescription = _T("Attempt was made to execute a method not marked with [implemented] in any relevant class");break;
  case WBEM_E_METHOD_DISABLED: //0x80041056
     szCode = _T("WBEM_E_METHOD_DISABLED");                     szDescription = _T("Attempt was made to execute a method marked with [disabled]");break;
  case WBEM_E_REFRESHER_BUSY: //0x80041057
     szCode = _T("WBEM_E_REFRESHER_BUSY");                      szDescription = _T("Refresher is busy with another operation");break;
  case WBEM_E_UNPARSABLE_QUERY: //0x80041058
     szCode = _T("WBEM_E_UNPARSABLE_QUERY");                    szDescription = _T("Filtering query is syntactically invalid");break;
  case WBEM_E_NOT_EVENT_CLASS: //0x80041059
     szCode = _T("WBEM_E_NOT_EVENT_CLASS");                     szDescription = _T("The FROM clause of a filtering query references a class that is not an event class (not derived from __Event)");break;
  case WBEM_E_MISSING_GROUP_WITHIN: //0x8004105A
     szCode = _T("WBEM_E_MISSING_GROUP_WITHIN");                szDescription = _T("A GROUP BY clause was used without the corresponding GROUP WITHIN clause");break;
  case WBEM_E_MISSING_AGGREGATION_LIST: //0x8004105B
     szCode = _T("WBEM_E_MISSING_AGGREGATION_LIST");            szDescription = _T("A GROUP BY clause was used. Aggregation on all properties is not supported");break;
  case WBEM_E_PROPERTY_NOT_AN_OBJECT: //0x8004105C
     szCode = _T("WBEM_E_PROPERTY_NOT_AN_OBJECT");              szDescription = _T("Dot notation was used on a property that is not an embedded object");break;
  case WBEM_E_AGGREGATING_BY_OBJECT: //0x8004105D
     szCode = _T("WBEM_E_AGGREGATING_BY_OBJECT");               szDescription = _T("A GROUP BY clause references a property that is an embedded object without using dot notation");break;
  case WBEM_E_UNINTERPRETABLE_PROVIDER_QUERY: //0x8004105F
     szCode = _T("WBEM_E_UNINTERPRETABLE_PROVIDER_QUERY");      szDescription = _T("Event provider registration query (__EventProviderRegistration) did not specify the classes for which events were provided");break;
  case WBEM_E_BACKUP_RESTORE_WINMGMT_RUNNING: //0x80041060
     szCode = _T("WBEM_E_BACKUP_RESTORE_WINMGMT_RUNNING");      szDescription = _T("Request was made to back up or restore the WMI repository while it was in use by WinMgmt.exe or in Windows XP or later the SVCHOST process that contains the Windows Management service");break;
  case WBEM_E_QUEUE_OVERFLOW: //0x80041061
     szCode = _T("WBEM_E_QUEUE_OVERFLOW");                      szDescription = _T("Asynchronous delivery queue overflowed from the event consumer being too slow");break;
  case WBEM_E_PRIVILEGE_NOT_HELD: //0x80041062
     szCode = _T("WBEM_E_PRIVILEGE_NOT_HELD");                  szDescription = _T("Operation failed because the client did not have the necessary security privilege");break;
  case WBEM_E_INVALID_OPERATOR: //0x80041063
     szCode = _T("WBEM_E_INVALID_OPERATOR");                    szDescription = _T("Operator is invalid for this property type");break;
  case WBEM_E_LOCAL_CREDENTIALS: //0x80041064
     szCode = _T("WBEM_E_LOCAL_CREDENTIALS");                   szDescription = _T("User specified a username/password/authority on a local connection. The user must use a blank username/password and rely on default security");break;
  case WBEM_E_CANNOT_BE_ABSTRACT: //0x80041065
     szCode = _T("WBEM_E_CANNOT_BE_ABSTRACT");                  szDescription = _T("Class was made abstract when its parent class is not abstract");break;
  case WBEM_E_AMENDED_OBJECT: //0x80041066
     szCode = _T("WBEM_E_AMENDED_OBJECT");                      szDescription = _T("Amended object was written without the WBEM_FLAG_USE_AMENDED_QUALIFIERS flag being specified");break;
  case WBEM_E_CLIENT_TOO_SLOW: //0x80041067
     szCode = _T("WBEM_E_CLIENT_TOO_SLOW");                     szDescription = _T("Client did not retrieve objects quickly enough from an enumeration");break;
  case WBEM_E_NULL_SECURITY_DESCRIPTOR: //0x80041068
     szCode = _T("WBEM_E_NULL_SECURITY_DESCRIPTOR");            szDescription = _T("Null security descriptor was used");break;
  case WBEM_E_TIMED_OUT: //0x80041069
     szCode = _T("WBEM_E_TIMED_OUT");                           szDescription = _T("Operation timed out");break;
  case WBEM_E_INVALID_ASSOCIATION: //0x8004106A
     szCode = _T("WBEM_E_INVALID_ASSOCIATION");                 szDescription = _T("Association is invalid");break;
  case WBEM_E_AMBIGUOUS_OPERATION: //0x8004106B
     szCode = _T("WBEM_E_AMBIGUOUS_OPERATION");                 szDescription = _T("Operation was ambiguous");break;
  case WBEM_E_QUOTA_VIOLATION: //0x8004106C
     szCode = _T("WBEM_E_QUOTA_VIOLATION");                     szDescription = _T("WMI is taking up too much memory");break;
  //case WBEM_E_TRANSACTION_CONFLICT: //0x8004106D
  //   szCode = _T("WBEM_E_TRANSACTION_CONFLICT");                szDescription = _T("Operation resulted in a transaction conflict");break;
  //case WBEM_E_FORCED_ROLLBACK: //0x8004106E
  //   szCode = _T("WBEM_E_FORCED_ROLLBACK");                     szDescription = _T("Transaction forced a rollback");break;
  case WBEM_E_UNSUPPORTED_LOCALE: //0x8004106F
     szCode = _T("WBEM_E_UNSUPPORTED_LOCALE");                  szDescription = _T("Locale used in the call is not supported");break;
  case WBEM_E_HANDLE_OUT_OF_DATE: //0x80041070
     szCode = _T("WBEM_E_HANDLE_OUT_OF_DATE");                  szDescription = _T("Object handle is out-of-date");break;
  case WBEM_E_CONNECTION_FAILED: //0x80041071
     szCode = _T("WBEM_E_CONNECTION_FAILED");                   szDescription = _T("Connection to the SQL database failed");break;
  case WBEM_E_INVALID_HANDLE_REQUEST: //0x80041072
     szCode = _T("WBEM_E_INVALID_HANDLE_REQUEST");              szDescription = _T("Handle request was invalid");break;
  case WBEM_E_PROPERTY_NAME_TOO_WIDE: //0x80041073
     szCode = _T("WBEM_E_PROPERTY_NAME_TOO_WIDE");              szDescription = _T("Property name contains more than 255 characters");break;
  case WBEM_E_CLASS_NAME_TOO_WIDE: //0x80041074
     szCode = _T("WBEM_E_CLASS_NAME_TOO_WIDE");                 szDescription = _T("Class name contains more than 255 characters");break;
  case WBEM_E_METHOD_NAME_TOO_WIDE: //0x80041075
     szCode = _T("WBEM_E_METHOD_NAME_TOO_WIDE");                szDescription = _T("Method name contains more than 255 characters");break;
  case WBEM_E_QUALIFIER_NAME_TOO_WIDE: //0x80041076
     szCode = _T("WBEM_E_QUALIFIER_NAME_TOO_WIDE");             szDescription = _T("Qualifier name contains more than 255 characters");break;
  case WBEM_E_RERUN_COMMAND: //0x80041077
     szCode = _T("WBEM_E_RERUN_COMMAND");                       szDescription = _T("The SQL command must be rerun because there is a deadlock in SQL");break;
  case WBEM_E_DATABASE_VER_MISMATCH: //0x80041078
     szCode = _T("WBEM_E_DATABASE_VER_MISMATCH");               szDescription = _T("Database version does not match the version that the WMI repository driver understands");break;
  case WBEM_E_VETO_DELETE: //0x80041079
     szCode = _T("WBEM_E_VETO_DELETE");                         szDescription = _T("WMI cannot execute the delete operation because the provider does not allow it");break;
  case WBEM_E_VETO_PUT: //0x8004107A
     szCode = _T("WBEM_E_VETO_PUT");                            szDescription = _T("WMI cannot execute the put operation because the provider does not allow it");break;
  case WBEM_E_INVALID_LOCALE: //0x80041080
     szCode = _T("WBEM_E_INVALID_LOCALE");                      szDescription = _T("Specified locale identifier was invalid for the operation");break;
  case WBEM_E_PROVIDER_SUSPENDED: //0x80041081
     szCode = _T("WBEM_E_PROVIDER_SUSPENDED");                  szDescription = _T("Provider is suspended");break;
  case WBEM_E_SYNCHRONIZATION_REQUIRED: //0x80041082
     szCode = _T("WBEM_E_SYNCHRONIZATION_REQUIRED");            szDescription = _T("Object must be written to the WMI repository and retrieved again before the requested operation can succeed");break;
  case WBEM_E_NO_SCHEMA: //0x80041083
     szCode = _T("WBEM_E_NO_SCHEMA");                           szDescription = _T("Operation cannot be completed; no schema is available");break;
  case WBEM_E_PROVIDER_ALREADY_REGISTERED: //0x80041084
     szCode = _T("WBEM_E_PROVIDER_ALREADY_REGISTERED");         szDescription = _T("Provider cannot be registered because it is already registered");break;
  case WBEM_E_PROVIDER_NOT_REGISTERED: //0x80041085
     szCode = _T("WBEM_E_PROVIDER_NOT_REGISTERED");             szDescription = _T("Provider was not registered");break;
  case WBEM_E_FATAL_TRANSPORT_ERROR: //0x80041086
     szCode = _T("WBEM_E_FATAL_TRANSPORT_ERROR");               szDescription = _T("Fatal transport error occurred");break;
  case WBEM_E_ENCRYPTED_CONNECTION_REQUIRED: //0x80041087
     szCode = _T("WBEM_E_ENCRYPTED_CONNECTION_REQUIRED");       szDescription = _T("User attempted to set a computer name or domain without an encrypted connection");break;
  case WBEM_E_PROVIDER_TIMED_OUT: //0x80041088
     szCode = _T("WBEM_E_PROVIDER_TIMED_OUT");                  szDescription = _T("A provider failed to report results within the specified timeout");break;
  case WBEM_E_NO_KEY: //0x80041089
     szCode = _T("WBEM_E_NO_KEY");                              szDescription = _T("User attempted to put an instance with no defined key");break;
  case WBEM_E_PROVIDER_DISABLED: //0x8004108A
     szCode = _T("WBEM_E_PROVIDER_DISABLED");                   szDescription = _T("User attempted to register a provider instance but the COM server for the provider instance was unloaded");break;
  case WBEMESS_E_AUTHZ_NOT_PRIVILEGED: //0x80042003
     szCode = _T("WBEMESS_E_AUTHZ_NOT_PRIVILEGED");             szDescription = _T("This computer does not have the necessary domain permissions to support the security functions that relate to the created subscription instance. Contact the Domain Administrator to get this computer added to the Windows Authorization Access Group");break;
  case WBEMESS_E_REGISTRATION_TOO_BROAD: //0x80042001
     szCode = _T("WBEMESS_E_REGISTRATION_TOO_BROAD");           szDescription = _T("Provider registration overlaps with the system event domain");break;
  case WBEMESS_E_REGISTRATION_TOO_PRECISE: //0x80042002
     szCode = _T("WBEMESS_E_REGISTRATION_TOO_PRECISE");         szDescription = _T("A WITHIN clause was not used in this query");break;
  case WBEM_E_RETRY_LATER: //0x80043001
     szCode = _T("WBEM_E_RETRY_LATER");                         szDescription = _T("Reserved for future use");break;
  case WBEM_E_RESOURCE_CONTENTION: //0x80043002
     szCode = _T("WBEM_E_RESOURCE_CONTENTION");                 szDescription = _T("Reserved for future use");break;
  default:
    szCode = _T("unknown");                                     szDescription = _T("Uknown error code");break;
  }

if (pszDescription != NULL)
  *pszDescription = szDescription;
return szCode;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*****************************************************************************
 * $Log: KDbgWbemErrorCode.cpp,v $
 * Revision 1.1  2010/02/03 22:10:50  ddarko
 * Created
 *
 *****************************************************************************/

