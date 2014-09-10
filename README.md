Stream
======

Stream has a lot of cool features, of which most have been used in various languages before, but put them together and you get a programming language that's pretty radical. Here are some of its design goals:

* [Declarative] - you tell the compiler what to do, and the compiler figures out how to do it
* [Reactive] - your program consists of a set of rules that specify how data should propogate when new input is received
* [Actor-oriented] - your program consists of a set of functions that asynchronously receive and respond to messages
* [Lazy evaluation] - Rule evaluation is delayed until the value is needed.
* [Inherently concurrent] - no need for threading-related confusion
* Stream-oriented - every variable is a stream that contains functions
* Minimal built-in syntax - there are only about 10 built-in operators. Most of the syntax is provided by a library called a dialect, which is itself written in Stream

[Declarative]: http://en.wikipedia.org/wiki/Declarative_programming
[Reactive]: http://en.wikipedia.org/wiki/Reactive_programming
[Actor-oriented]: http://en.wikipedia.org/wiki/Actor_(programming)
[Inherently concurrent]: http://en.wikipedia.org/wiki/Concurrent_computation
[Lazy evaluation]: http://en.wikipedia.org/wiki/Lazy_evaluation

**Note that at the time of this writing (Aug 20, 2014) there is no implementation for Stream. Work is in progress on that front.**

Hello World
-----------

```stream
<= Console.write('Hello World')
```

Built-in syntax
---------------

* `target = source`, `target <= source`, `source => target` - Streams from the source to the target. Any functions that the source stream contains, both now and in the future, are forwarded into the target stream. If `target` is not supplied, the current function's output stream is assumed. If `source` is not supplied, the current function's input stream is assumed.
* `target source`, `target <- source`, `source -> target` - Pipes from the source to the target. Each function in target will be executed for each function in source. For example: `(2 +, 5 +, 7 +) <- (10, 20)` evaluates to `(12, 15, 17, 22, 25, 27)`. If `target` is not supplied, the current function's output stream is assumed. If `source` is not supplied, the current function's input stream is assumed.
* `{...}` - Returns a function, and defines `in`, `out`, and `self` as the input stream, output stream, and current function respectively. Also creates a scope, so that any streams created with `+` will not be accessible outside. Streams will not be returned implicitly, so `{1, 2} <- .` will return an empty stream.
* `[...]` - Returns a function, but does not define `in`, `out`, or `self`. Also does not create a new scope, so created streams will be accessible outside. Streams will be returned implicitly, so `[1, 2] <- .` will return a stream of `1` and `2`.
* `(...)` - Like `[...]`, but evaluates immediately. Streams will be returned implicitly, so `(1, 2)` will return a stream of `1` and `2`.
* `.prop: value` - The `:` returns an inline function that returns `value` if `.prop` is supplied as input. Inline means that it adds its code to the containing function instead of creating a new function. For example, `[.answer: 42].answer` will return `42`.
* `'abc'`, `"def"`, `.ghi` - Returns a function with string-like properties.
* `42`, `-3.14`, `1e100` - Retrurns a function with number-like properties.
* `+my_stream` - Creates a new, empty stream, scoped inside the closest `{...}`.
* `my_stream #` - Returns the length of `my_stream` as a number. The `#`, `$`, and `^` operators are unique because they do not operate on the contents of a stream, but on the stream itself. As a consequence, they will not write the length to their output stream until no more functions can be written to the input stream.
* `my_stream $` - Returns the last function of `my_stream`. Like `#`, it operates on the stream itself.
* `my_stream ^` - Returns the first function of `my_stream`. Like `#`, it operates on the stream itself.

Getting Started
---------------

There are only 2 types exposed in the Stream language: streams and functions. Variables are streams. Streams are un-ordered lists of functions. Funcions, when called, return a stream. It might sound confusing, but here are a few examples:

```stream
+my_stream = (2, 3, 5, 7, 11)
```
Let's break that down:
* `+my_stream` - Creates a new stream called `my_stream`. The `+` is like `var` in javascript. It sets the scope of `my_stream`.
* `=` - Streams from the right side to the left side. Whatever the right side evaluates to will be streamed into `my_stream`. We could have used `<=` instead of `=`. They do exactly the same thing. As you've probably guessed, there is a `=>` operator that streams from the left to the right.
* `2`, ..., `11` - These literals each return a stream containing a function that contain methods that you'd expect a number to have, like `+`, `-`, `*`, etc.
* `(2, 3, 5, 7, 11)` - Combines each number stream into a single stream.

Let's print each number:
```stream
<= Console.write(my_stream)
// or
<= Console.write my_stream
```
There's more here than may seem at first:
* `<=` - The only way to use external OS features, like the console, filesystem, or access other processes is to stream out of the top level (not inside a function) of the main file. `Console.write` doesn't do anything with the console. It can't. What it does do is return a special stream. When that stream is streamed out of the main file with `<=`, the console is updated.
* `Console` - Nothing too interesting here, just accessing the stream called `Console`, which was defined by the dialect. In this case, the `Console` stream contains one function.
* `.write` - A dot followed by an identifier returns a string. So `.write` is the same as `'write'`. And when I say string, I mean a stream containing a function that has stringy methods, like `.substr`, `.length`, etc.
* `Console 'write'` - A stream followed by another stream calls each function of the first stream with each function of the second stream as arguments. So that's (the length of stream 1) * (the length of stream 2) function calls. In this case, both the `Console` and the `'write'` stream only have one function, so `Console` is only called once, with `'write'` as the argument. Guess what's returned? A stream containing one function!
* `(my_stream)` - As stated before, parenthesis create a stream, but since `my_stream` is already a stream, they aren't necessary. In fact, since everything is a stream, the only time you would have to use parenthesis is when you'd like to group something into one stream, like `(1, 2, 3)`.
* `Console.write my_stream` - This will call the result of `Console.write` 5 times, each time with one of the functions in `my_stream` as the argument. Each number will be printed.

Let's find all the primes less than 1000:
```stream
// Lazily calculate all natural numbers
+N = 1
N -> {in + 1 => N}

// Calculate primes
+primes = N > 1 < 1000 -> {
    <= in % (N > 1 < in) ~ 0 #~0 -> [in]
}
```
* `+N = 1` - Creates a new stream.
* `N -> {in + 1 => N}` - Foreach `N` as `in`, add `in + 1` to the `N` stream. Each time a number is added, the function is called again, adding another function. If this were not lazily evaluated, it would be an infinite loop.
* `N > 1 < 1000` - `>` is a global variable declared by the dialect. `N >` calls each function (number) in `N` with `>` as an argument. This returns a stream of greater than functions. Instead of returning a boolean, comparison functions return a stream containing the first operand if true, or an empty stream if false. So `N > 1` will return a stream of each `N` that is greater than `1`. `< 1000` filters the stream in the same way.
* `in % (N > 1 < in)` - Calculates the remainder of `in` divided by every number less than it.
* `~ 0` - The `~` operator compares the value of a number or string, as opposed to the function itself like `==`. So `~ 0` selects all the remainders equal to zero.
* `#~0` - The `#` operator returns the length of the stream. So `# ~ 0` returns a stream containing a single `0` if there are no divisors, or an empty stream if there is a divisor. I omitted the spaces only because I think it's cleaner that way.
* `-> [in]` - `[in]` will be called once if there are no divisors. It returns `in`, which is the number being tested for primality. So if the number is prime, it's argument is returned. If not, an empty stream is returned. The result of each number being tested is combined into the `primes` stream.

The `primes` stream is bound to the `N` stream. That means if the `N` stream didn't generate its own numbers, but used some kind of asynchronous generation, like reading them from the console, everything would still work. Every time you typed in a number, the `N` stream would update, and the `primes` stream would automatically update if the new number was prime.

Code examples
-------------

Here's some code in python, taken from [wikipedia]:
[wikipedia]: http://en.wikipedia.org/wiki/List_comprehension#Python

```python
S = [2 * x for x in range(101) if x ** 2 > 3]
```
Here's the same thing in Stream:
```stream
+S = range[:101] -> {in * in > 3} -> 2 *
```
