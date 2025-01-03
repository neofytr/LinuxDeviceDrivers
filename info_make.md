### Full Example Makefile

```makefile
# 1. Define the kernel source directory
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

# 2. Define the current working directory
PWD := $(shell pwd)

# 3. Specify the kernel object(s) to be built
obj-m += hello.o

# 4. Target: Build the module
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

# 5. Target: Clean up build artifacts
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
```

---

### Explanation

---

#### **Line 1: Kernel Source Directory**
```makefile
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
```
- **`KERNELDIR`**: A variable pointing to the kernel source tree used for building the module.
  - **`/lib/modules`**: The directory where kernel modules and headers are stored on the system.
  - **`$(shell uname -r)`**: A shell command executed within the Makefile to get the currently running kernel version (e.g., `5.15.0-rc7`).
  - **`/build`**: A subdirectory containing the build environment for the kernel.
- **`?=`**: Conditional assignment. If `KERNELDIR` is already set in the environment, this line does nothing. If it is not set, it assigns the specified value.

---

#### **Line 2: Current Working Directory**
```makefile
PWD := $(shell pwd)
```
- **`PWD`**: A variable holding the current working directory.
  - **`$(shell pwd)`**: Executes the `pwd` command in the shell and stores the output (e.g., `/home/user/kernel_module`).
- **`:=`**: Immediate assignment. The value of `PWD` is evaluated and stored immediately during the Makefile's parsing.

---

#### **Line 3: Specify Kernel Object(s)**
```makefile
obj-m += hello.o
```
- **`obj-m`**: A special variable used by the kernel build system to specify loadable modules.
  - Each file listed here (e.g., `hello.o`) corresponds to a source file (e.g., `hello.c`). The kernel build system has a way to build all the source files it finds in the module source directory given to it to .o files.
- **`+=`**: Appends `hello.o` to the existing value of `obj-m` if it already exists, or initializes it if it does not.

---

#### **Line 4: Build the Module**
```makefile
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
```
- **`all:`**: Declares a target named `all`, typically the default action when `make` is run without arguments.
- **`$(MAKE)`**: Refers to the `make` command itself.
  - **Why `$(MAKE)` and not `make`?** Using `$(MAKE)` ensures that any environment variables passed to the parent `make` are also passed to recursive invocations.
- **`-C $(KERNELDIR)`**: Changes the directory to `KERNELDIR` and executes the kernel's build system there.
  - **Why `-C`?** The kernel build system requires being invoked from its own directory.
- **`M=$(PWD)`**: Tells the kernel build system to look for module source files in the `PWD` directory.
- **`modules`**: A specific target in the kernel build system that compiles external modules.

---

#### **Line 5: Clean Build Artifacts**
```makefile
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
```
- **`clean:`**: Declares a target named `clean`, used for cleaning up build artifacts like `.o`, `.ko`, and `.mod.*` files.
- **`$(MAKE)`**: Again invokes `make`.
- **`-C $(KERNELDIR)`**: Changes the directory to the kernel build system directory.
- **`M=$(PWD)`**: Informs the kernel build system which directory's artifacts should be cleaned.
- **`clean`**: A built-in kernel build system target that removes temporary and generated files.

---

### Symbol and Variable Breakdown
1. **`?=` (Conditional Assignment)**: Assigns a value to a variable only if it is not already defined.
   - Example: `FOO ?= bar` assigns `bar` to `FOO` if `FOO` is unset.

2. **`:=` (Immediate Assignment)**: Assigns a value immediately, evaluating any expressions or shell commands.
   - Example: `PWD := $(shell pwd)` stores the output of `pwd` in `PWD`.

3. **`+=` (Append)**: Appends the value to an existing variable or initializes it if it is unset.
   - Example: `VAR += value` appends `value` to `VAR`.

4. **`$(shell command)`**: Executes a shell command and captures its output.
   - Example: `$(shell uname -r)` captures the kernel version string.

5. **`$(VARIABLE)`**: References the value of a variable.
   - Example: `$(PWD)` expands to the value of `PWD`.

6. **`-C` (Change Directory)**: A `make` flag that changes the directory before executing commands.

---

### How the Build Process Works
1. **Run `make`**:
   - `make` defaults to the `all` target.
   - The `all` target invokes `$(MAKE)` in the kernel build directory, specifying the current directory (`M=$(PWD)`) as the location of the external module source.

2. **Kernel Build System**:
   - The kernel's `Makefile` includes the external module directory (`M=$(PWD)`).
   - It compiles `hello.c` into:
     - `hello.o`: Compiled object file.
     - `hello.ko`: Loadable kernel module.

3. **Run `make clean`**:
   - Invokes the kernel build system's `clean` target to remove build artifacts.
