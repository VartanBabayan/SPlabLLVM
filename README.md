# LLVM invoke printf to the IR code Pass

To build it you need:
 [llvm-project](https://github.com/llvm/llvm-project)

Next move this folder to **llvm-project/llvm/lib/Transforms**

In folder Transforms open CMakeLists.txt and write

**add_subdirectory(InvokePrintf)**

Now build your llvm and run Pass with command:

**opt -load build/lib/llvmInvokePrinft.so -ir-instrumentation <.bc> /dev/null**



