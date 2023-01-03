# Embedded Systems Architecture - Second Edition

<a href="https://www.packtpub.com/product/embedded-systems-architecture-second-edition/9781803239545?utm_source=github&utm_medium=repository&utm_campaign=9781803239545"><img src="https://static.packt-cdn.com/products/9781803239545/cover/smaller" alt="Embedded Systems Architecture - Second Edition" height="256px" align="right"></a>

This is the code repository for [Embedded Systems Architecture - Second Edition](https://www.packtpub.com/product/embedded-systems-architecture-second-edition/9781803239545?utm_source=github&utm_medium=repository&utm_campaign=9781803239545), published by Packt.

**Design and write software for embedded devices to build safe and connected systems**

## What is this book about?
Embedded Systems Architecture begins with a bird’s-eye view of embedded development and how it differs from the other systems that you may be familiar with. This book will help you get the hang of the internal working of various components in real-world systems. 

This book covers the following exciting features:
* Participate in the design and definition phase of an embedded product
* Get to grips with writing code for ARM Cortex-M microcontrollers
* Build an embedded development lab and optimize the workflow
* Secure embedded systems with TLS
* Demystify the architecture behind the communication interfaces
* Understand the design and development patterns for connected and distributed devices in the IoT
* Master multitasking parallel execution patterns and real-time operating systems
* Become familiar with Trusted Execution Environment (TEE)

If you feel this book is for you, get your [copy](https://www.amazon.com/dp/1803239549) today!

<a href="https://www.packtpub.com/?utm_source=github&utm_medium=banner&utm_campaign=GitHubBanner"><img src="https://raw.githubusercontent.com/PacktPublishing/GitHub/master/GitHub.png" 
alt="https://www.packtpub.com/" border="5" /></a>

## Instructions and Navigations
All of the code is organized into folders. For example, Chapter02.

The code will look like the following:
```
/* Jump to non secure app_entry */
 asm volatile("mov r12, %0" ::"r"
 ((uint32_t)app_entry - 1));
 asm volatile("blxns r12" );
```

**Following is what you need for this book:**
If you're a software developer or designer looking to learn about embedded programming, this is the book for you. You’ll also find this book useful if you’re a beginner or a less experienced embedded programmer on a quest to expand your knowledge on embedded systems.

With the following software and hardware list you can run all code files present in the book (Chapter 1-11).
### Software and Hardware List
| Chapter | Software required | OS required |
| -------- | ------------------------------------ | ----------------------------------- |
| 1-11 | GNU Embedded ARM toolchain | Windows, Mac OS X, and Linux (Any) |


We also provide a PDF file that has color images of the screenshots/diagrams used in this book. [Click here to download it](https://packt.link/kVMr1).

### Related products
* Embedded Programming with Modern C++ Cookbook [[Packt]](https://www.packtpub.com/product/embedded-programming-with-modern-c-cookbook/9781838821043?utm_source=github&utm_medium=repository&utm_campaign=9781838821043) [[Amazon]](https://www.amazon.com/dp/183882104X)

* Embedded Systems Architecture - Second Edition [[Packt]](https://www.packtpub.com/product/modern-computer-architecture-and-organization-second-edition/9781803234519?utm_source=github&utm_medium=repository&utm_campaign=9781803234519) [[Amazon]](https://www.amazon.com/dp/1803234512)

## Get to Know the Author
**Daniele Lacamera**
is a software technologist and researcher with vast experience in software design and development on embedded systems. He works as a senior software engineer at wolfSSL Inc., mostly focusing on security, secure boot, and integration with connected systems. He is an expert in TCP/IP and transport protocols design and optimization, with more than 20 academic publications on the topic. He supports free software, contributing to several projects, including the Linux kernel.
