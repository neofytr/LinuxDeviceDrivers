# Device Drivers

Device Drivers are distinct "black boxes" that make a particular piece of hardware respond to a well-defined internal programming interface; they hide completely the details of how a device works. 

User activities are performed by means of a set of standardized calls that are independent of the specific driver; mapping those calls to device-specific operations that act on real hardware is then the role of the device driver.

This programming interface is such that drivers can be built separately from the rest of the kernel and "plugged in" at runtime when needed.

# The Role of the Device Driver

The role of a device driver is providing *mechanism*, not *policy*.

Most programming problems can be split into two parts: "what capabilities are to be provided" (the mechanism) and "how those capabilties can be used" (the policy).

If the two issues are addressed by different parts of the program, or even by different programs altogether, the software package is much easier to develop and to adapt to particular needs.

When writing device drivers, write kernel code to access the hardware (i.e, provide a mechanism), but don't force particular policies on the user, since different users have different needs.

The driver should deal with making the hardware available, leaving all the issues about *how* to use the hardware to the applications. A driver, then, is flexible if it offers acces to the hardware capabilities without adding constraints.

Sometimes, however, policy decisions must be made. For example, a digital I/O driver may only offer byte-wide access to the hardware in order to avoid the extra code needed to handle individual bits.

The device driver is a software layer that lies between the applications and the actual device. The privileged role of the driver allows the driver programmer to choose exactly how the device should appear; different drivers can offer different capabilities, even for the same device.

Policy-free drivers have a number of typical characteristics. These include support for both synchronous and asynchronous operation, the ability to be opened multiple times, they ability to exploit the full capabilties of the hardware, and the lack of software layers to "simplify things" or provide policy-related operations.

Many device drivers, indeed, are released together with user programs to help with configuration and access to the target device. Often a client library is provided as well, which provides capabilities that do not need to be implemented as part of the driver itself.

User programs are an integral part of a software package and that even policy-free packages are distributed with configuration files that apply a default behavior to the underlying mechanisms.

# Splitting the Kernel

In a Unix system, several concurrent *processes* attend to different tasks.

Each process asks for system resources, be it computing power, memory, network connectivity, or some other resource. 

The kernel is the big chunk of executable code in charge of handling all such requests.

The Kernel's role can be split into:

## Process Management

The kernel is in charge of creating and destroying processes and handling their connection to the outside world.