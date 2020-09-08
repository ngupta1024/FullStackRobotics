# LibCppIssues

## Static
1. Non-const static members cannot be initialized in the class and should be initialized in the global scope
2. Static member functions are only needed if you want to do something irrespective of objects and only bound to the class.
3. Static can be interpretted as global variables in most cases. Private static members can be accessed by the class members and public static can be accessed outside of the class.

## Inheritance
1. Dynamic Pointer cast will only work for polymorphic class (with atleast one virtual function).
2. 
