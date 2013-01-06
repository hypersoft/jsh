jsh
===

### *The Hypersoft JavaScript Shell*

>Hello user, our repository is currently undergoing initial construction. Please
be patient while we see to important matters such as licensing and initial code
uploads.

#### Introduction
Jsh is a JavaScript Shell written in C by [Triston J. Taylor](https://facebook.com/pc.wiz.tt)
for GNU/Linux style Unix systems. The shell is designed for Unix style systems 
on the premise, that the lead developer does not have the hardware to test and
design for a wider user base. Moreover the maintainer does not care to offer
support for other, platforms being that supporting a system he can't test is
apparently, an excercise in futility.

The author maintains several pages in the Facebook network, most notably are
[Unix4u](https://facebook.com/unix4u), and [BASH Scripting](https://facebook.com/alt.bash).
Triston, is known to be a knowledgeable source of information about computers, 
electronics and well, pretty much, more than a little bit of everything. He has knowledge
and experience using more than 10 different programming languages which he has
acquired over a period of 15 years. His first taste of actual programming was
with a web browser using NetScape's JavaScript. Don't let him fool you, he
plays favorites with programming languages, and there are very few he considers
worth the effort.

JavaScript was designed and concieved at NetScape by Brendan Eich, many years
ago, before the, web was the web we know today. The modern JavaScript standard
is maintained and developed by the [ECMA](http://www.ecma.org). 
The current design standard of jsh, is built on the Gnome project's [Seed
Engine](https://live.gnome.org/Seed) version 3.2, which is based on The Open 
Source Apple [Safari WebKit](http://www.webkit.org/) JavaScriptCore.

Jsh aims to be a great platform for scripting in the Unix world. If any other
platforms may benefit from this overview then *good for them*. But user be warned,
we will not break our backs, api, or stability to support foolishness. One
environment is hard enough to get right.

The use of Gnome Seed allows jsh to interface, with most of the Gnome
programming platform through GObjectIntrospection. This includes notable
software technologies like GTK+ and WebKitGtk, but that's not what Jsh is about.
Jsh is more or less about what the author belives a JavaScript shell should be.

JavaScript, while novel and extremely utilitarian, can be quite slow with the 
"get up and go" when it comes to heavy performance, but the author knows better.
He knows how a processor works from inside, as he has taught himself coding in 
JavaScript, Java, Perl, C and Assembler.

Slow? Oh, hell no! Not unless you are doing it wrong! JavaScript and C were virtually
made for each other, but from their backgrounds, one certainly wouldn't guess it
right off. Jsh is going to be that "thing" that shows them all how it is supposed
to be done. Interfacing with shared libraries for the gruntwork, and applying
all polish and process control through scripting.
<hr>
#### How it's done
In a word, [dyncall](http://dyncall.org) a dynamic symbol loader written for
various platforms. Binding JavaScript with this library gives Jsh the power to be.
The power to be anything you can dream of and more. Anything that is, if you
know your code. You can write libraries in any language with a C compatible
interface, and run them from Jsh with ease. We have taken great care to analyse
what JavaScript can and can't do the C way, and we built a bridge to get across
that river using dyncall, with relative ease.

What JavaScript Cannot Do:

	1. Readily use parameters as return types
	2. Allocate Value Typed Buffers
	3. Free Value Typed Buffers
	4. Load Shared libraries (or applications) and access symbols from within them
	5. Match the performance of a production status compiled language.
<markup theme='hypersoft'>
