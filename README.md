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

	1. Readily use parameters as return types "top-level stack parameters" are protected
	2. Allocate and free value typed buffers
	3. Write to value typed buffers
	4. Load shared libraries (or applications) and access symbols from within them
	5. Match the performance of a production status compiled language.
	6. Native structures, unions, enums, calls and call backs

The Seed project has broken a lot of these rules, but left the end user with
something to be desired for. They boarded up the windows, and sealed the doors
shut after they barricaded the goldmine under a web of code we would rather
not try to decipher. And that sucks. For example, what if the user doesn't care for
GObjects and Instrospection? What then? A tool that was otherwise headed for
greatness is condemned to lurk in the shadows as yet another "could have been".

We didn't like that idea. The project has made some great headroom that this
author would dare not enter into without a fat paycheck to follow. In other
words, its a useful work that we will allow you to take advantage of as well
as the C additions we have implemented.
	 
What Jsh Can Do:

	1. Allocate and free value typed buffers
	2. Load shared libraries (or applications) and access symbols from within them
	3. Closely match the perfomance of a production status compiled language
	4. Native calls

What Jsh Plans to Do:

	 1. Write to value typed buffers
	 2. Native structures, unions, and call backs
	 3. Unix style script interpretation with execution status checking
	 4. Arbitrary file execution
	 5. Standard input execution
	 6. Command line statement evaluation
	 7. Interactive input execution
	 8. /etc/jsh.rc init script
	 9. ~/.jshrc init script
	10. Shared Library and symbol white-listing at system level
	11. Bypass user or system init scripts (exclusive to white-listing)
	12. System logfile of information useful to execution diagnostics
	13. Ability to run scripts as a daemon process
	14. Official Github hosted script repository
	15. User Github hosted script repository

<hr>
Jsh has no intention to be a POSIX shell, but if you work at it, you might be
able to build one with it in no time at all, without all of the binary overhead.
It isn't until we reach completion of the above task list that version 1.0 of
jsh will be anounced for general user incorporation.

If you would like to help out with development or have questions feel free to 
contact the developer here on [GitHub](https://github.com/hypersoft), [Facebook](https://facebook.com/pc.wiz.tt), or [Gmail](mailto:pc.wiz.tt@gmail.com)
<markup theme='hypersoft'>
