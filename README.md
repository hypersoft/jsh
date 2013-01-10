jsh<markup theme='hypersoft'>
===

### *The Hypersoft JavaScript Shell*

	Platform: GNU/Linux
	Language: C

	Author: Copyright (C) Triston J. Taylor 2013 All rigths reserved
	Contact: <pc.wiz.tt@gmail.com>

	Dual License: GPL V.3 (Free), BSD Like, Contributary 2-Clause (Commercial) see LICENSE.md

><hr>

#### Status

	Repository Initialization

><hr>

#### Introduction
Jsh is a JavaScript shell written in C by [Triston J. Taylor](https://facebook.com/pc.wiz.tt)
for [GNU/Linux systems](http://www.gnu.org/gnu/linux-and-gnu.html).
The shell is designed for [Unix style systems](http://www.unix.org/) on the 
premise, that the author does not have the hardware to test and design for a 
wider user base. Moreover the maintainer does not care to offer support for 
other, platforms being that supporting a system he can't test is apparently, an 
excercise in futility.

The author maintains several pages in the Facebook network, most notably are
[Unix4u](https://facebook.com/unix4u), and [BASH Scripting](https://facebook.com/alt.bash).
Triston, is known to be a knowledgeable source of information about computers, 
electronics and well, pretty much, more than a little bit of everything. He has knowledge
and experience using more than 10 different programming languages which he has
acquired over a period of 15 years. His first taste of actual programming was
with a [Phillips Magnavox WebTV](http://en.wikipedia.org/wiki/WebTV_Networks#Early_history)
using [Netscape](http://en.wikipedia.org/wiki/Netscape)'s JavaScript. Don't let him fool you, he
plays favorites with programming languages, and there are very few he considers
worth the effort.

JavaScript was designed and concieved at Netscape by
[Brendan Eich](http://en.wikipedia.org/wiki/Brendan_Eich), many years
ago, before the, web was the web we know today. The modern JavaScript standard
is maintained and developed by the [ECMA](http://www.ecma-international.org). 
The current design standard of Jsh, is built with the [Gnome](http://gnome.org)
project's [LGPL Seed Engine](https://live.gnome.org/Seed) version 3.2, which is
based on The Open Source Apple [Safari WebKit](http://www.webkit.org/)
[JavaScriptCore](http://trac.webkit.org/wiki/JavaScriptCore).

Jsh aims to be a great platform for scripting in the Unix world. If any other
platforms may benefit from this overview then *good for them*. But user be warned,
we will not break our backs, API, or stability to support foolishness. One
environment is hard enough to get right.

The use of Gnome Seed allows jsh to interface, with most of the Gnome
programming platform through 
[GObjectIntrospection](https://live.gnome.org/GObjectIntrospection). This 
includes notable software technologies like [GTK+](http://www.gtk.org/) and
[WebKitGtk+](http://webkitgtk.org/), but that's not what Jsh is about.
Jsh is more or less about what the author belives a JavaScript shell should be.

JavaScript, while novel and extremely utilitarian, can be quite slow with the 
"get up and go" when it comes to heavy performance, but the author knows better.
He knows how a processor works from inside, as he has taught himself coding in 
JavaScript, [Java](http://www.java.com/), [Perl](http://www.perl.org/),
[C](http://en.wikipedia.org/wiki/C_\(programming_language\)) and
Intel [x86 Assembler](http://en.wikipedia.org/wiki/X86_assembly_language).

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

####What JavaScript Cannot Do:

* Readily use parameters as return types "top-level stack parameters" are protected
* Allocate and free value typed buffers
* Load shared libraries (or applications) and access symbols from within them
* Match the performance of a production status compiled language.
* Native structures, unions, enums, calls and call backs

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
	 
####What Jsh Can Already Do:

* Load/Unload shared libraries & applications
* Locate symbols in shared libraries & applications
* Native procedure prototype scripting (unlimited definitions per symbol)
* Allocate and free native C types or arrays (buffers)
* Pass native C types and arrays as parameters to native functions
* Retrieve javascript primitives or arrays from native C types (unbuffering)

><hr>

####What's up next:

* Create native C types from javascript primitives

><hr>

####Backburner:

* Command line statement evaluation
* Command line syntax check
* Command line file execution
* Compile Standard input mode
* Unix shebang script interpretation
* Interactive input mode
* System initialization script: (/etc/jsh.rc)
* User initialization script: (~/.jshrc init script)
* Bypass init scripts
* System adminstration: Whitelisting (/etc/jsh/shared.wl)
* System administration: Blacklisting (/etc/jsh/shared.bl)
* Native structures
* Procedure call backs
* System logfile
* Possibly support daemonization (needs review)

<hr>

####How to build:

	 git clone https://github.com/hypersoft/jsh.git;
	 cd jsh && make;

>Currently there are no install or clean targets. The resulting file is located
in the bin directory: `./bin/jsh`
<hr>

####Hello World jsh:

	 puts = new jsh.library("libc.so.6").find("puts").declare(jsh.type.int, jsh.type.string);
	 puts("Hello World!");
	 Seed.quit();

Do try not to venture out too far into the project's internals as there is no
solid definition of how we want to do anything other than the "Hello World"
example given above. While we are using Seed now, that could change as the project
matures and is eventually able to load Seed on its own.

><hr>

Jsh has no intention to be a
[POSIX shell](http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html),
but if you work at it, you might be able to build one with it in no time at all,
without all of the binary overhead. It isn't until we reach completion of the 
above task list that version 1.0 of jsh will be anounced for general user incorporation.

If you have questions feel free to contact the developer here on 
[GitHub](https://github.com/hypersoft),
[Facebook](https://facebook.com/pc.wiz.tt), or 
[Gmail](mailto:pc.wiz.tt@gmail.com)

