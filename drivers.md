# Device Drivers

Device Drivers are distinct "black boxes" that make a particular piece of hardware respond to a well-defined internal programming interface; they hide completely the details of how a device works. 

User activities are performed by means of a set of standardized calls that are independent of the specific driver; mapping those calls to device-specific operations that act on real hardware is then the role of the device driver.

This programming interface is such that drivers can be built separately from the rest of the kernel and "plugged in" at runtime when needed.