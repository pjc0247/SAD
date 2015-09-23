SAD(Super Annoying & Dirty) AOP with C++
----
Aspect Oriented Programming in C++.

Overview
----
```c++
// inject 'logme', 'becnhmark' aspects into 'foo'
void foo() { $$(logme) $$(benchmark)
  /* ... */
}
```

To Make Your Own Aspect
----
```c++
class FooAspect : IFunctionLifeContext<> {
public:
  virtual void OnEnter(const std::string &fname) {
    /* TODO : aspect initialization code goes here */
  }
  virtual void OnLeave(const std::string &fname) {
    /* TODO : aspect cleanup code goes here */
  }
}
```

Aspects can accept arguments.
```cpp
class FooAspect : IFunctionLifeContext<int, int> {
  virtual void OnEnter(const std::string &fname, int a,int b) {
    printf("%d %d\n", a,b);
  }
  virtual void OnLeave(const std::string &fname) {
    /* additional parameters are not passed to OnLeave method */
  }	
}
```
```cpp
void foo(int a,int b) { $$(foo, a,b)
}
```

Usage
----
As a original purpose, you can inject aspects to place `$$(aspect_name)` next to the left-bracket of the function.
```cpp
same as Overview's example
```

Aspects can be used in middle of the function. See example code below 
```cpp
void foo() {
	/* ... uninteresed area */
	
	$$(benchmark) {
		/* a code block DAT you wants to benchmark */
	}
	
	/* ... uninteresed area */
}
```
