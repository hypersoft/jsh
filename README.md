jsh<markup theme='hypersoft'>
===

### *The Hypersoft JavaScript Shell*

	Platform: GNU/Linux
	Language: C

	Author: Copyright (C) Triston J. Taylor 2013 All rigths reserved
	Contact: <pc.wiz.tt@gmail.com>

	Free Software License: GPL V3

	Commercial License: BSD 2-Clause

><hr>

#### Licensing Information
We offer a commercial BSD 2-Clause license for four reasons:

>**1.** Entities who have made considerable contributions to this work with,
permisive licensing shall not be denied the right to prosper from this work.

>**2.** Anyone who is creating a commercial product, shall be able to use our
software, but will also share in the financial responsibilty of its development.

>**3.** Bearing the financial duties should mean gaining the rights, to a
marketable advantage.

>**4.** Anything less, would be uncivilized.

<br/>
Following is a list of commercially qualified entities with their respective
contribution(s) to this work:

* Apple Inc. (JavaScriptCore)
* Dyncall.org (Dyncall Library)
* GitHub Inc. (Code Hosting)
* Gnome.org (Seed Project)

If you are interested in purchasing a commercial license, contact the author for
pricing inquiries. If you are upset by our licensing, get over it. We have found,
our reasoning to be sound and fair to everyone rather than being unfair, and 
uncompromising.

If you would like to make a $25.00 donation, please contact the author for
information as to where you can send your donation via snail mail. If you would
like to make a smaller donation, please send your money to a reputable charity
organization that could actually do something with it, such as
[The American Red Cross](http://www.redcross.org),
[The Wikipedia](http://en.wikipedia.org/wiki/Donation), or
[The Free Software Foundation](http://www.fsf.org).

Thank you.

*-- Healthy competition promotes healthy innovation.*

<hr>

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
* Retrieve javascript primatives or arrays from native C types (unbuffering)

><hr>

####What's up next:

* Create native C types from javascript primatives

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

Currently there are no install or clean targets. The resulting file is located
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

####Closing Notes From the Author
Jsh has no intention to be a [POSIX shell](http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html),
but if you work at it, you might be able to build one with it in no time at all,
without all of the binary overhead. It isn't until we reach completion of the 
above task list that version 1.0 of jsh will be anounced for general user incorporation.

If you would like to help out with development or have questions feel free to 
contact the developer here on [GitHub](https://github.com/hypersoft), [Facebook](https://facebook.com/pc.wiz.tt), or [Gmail](mailto:pc.wiz.tt@gmail.com)

<hr>

###More Legal Stuff

####JavaScriptCore Copyright (C) 2006-2008

	Copyright (C) 2006 Apple Inc. All rights reserved.
	Copyright (C) 2008 Alp Toker <alp@atoker.com>

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
	PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
	EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
	PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
	PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
	OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

><hr>

####Seed JavaScriptCore GObjectIntroSpection Bindings Copyright (c) 2009

	Copyright (C) Robert Carr 2009 <carrr@rpi.edu>

	Seed is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 2 of
	the License, or (at your option) any later version.

	Seed is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	You should have received a copy of the GNU Lesser General Public License
	along with Seed.  If not, see <http://www.gnu.org/licenses/>.

><hr>

####Dyncall Symbol Loader Library Copyright (C) 2007-2012

	Copyright (C) 2007-2012 Daniel Adler dadler AT uni-goettingen DOT de>, 
	Copyright (C) 2007-2012 Tassilo Philipp tphilipp AT potion-studios DOT com

	Permission to use, copy, modify, and distribute this software for any
	purpose with or without fee is hereby granted, provided that the above
	copyright notice and this permission notice appear in all copies.

	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
	WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
	OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

><hr>

<div id=legalFinePrint><font size=1>
Sublicensing of commercial licenses are expressly prohibited without the formal
written consent of the respective project author. Some individuals may qualify
for a commercial license due to sizable contributions, but are not listed here
for brevity, contact the project author for inquiries into this matter. 
Individuals and entities listed throughout this work do not constitute an
endorsement of this work, nor does a mention of any entity identifier constitute
agreement with any views or opinions portrayed or expressed by this work, its
primary author or contributors. All trademarks and copyrights are the respective
properties of the respective owners. This document may not by any means be removed
from a source distribution of this work, without express written consent from the
copyright holder of this work. Modification of this document is strictly prohibited.
Copyright (C) 2013 Triston J. Taylor All rights reserved.
</font></div>

