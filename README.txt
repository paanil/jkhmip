Shadow mapping school project
=============================

Contents of this file:

* ABOUT THE PROJECT
* LICENSE


ABOUT THE PROJECT
=================

This software was developed as a school project.
The goal of the project was to create a rendering
engine focusing on shadow mapping.

Simple shadow mapping works for directional and
spot lights and the basics of a limited rendering
engine are in place.

IMPORTANT: The software is not ready to be used
---------- in any project larger than a simple
demonstrative application. It lacks proper scene
management, some parts have just been hacked to work
(like the UBO for lights, ugh), other areas were
started but never finished (e.g. the UI) and overall
it needs lots of refactoring and clean up.


LICENSE
=======

See COPYING for the GNU GENERAL PUBLIC LICENSE


What is not covered by the GPL
------------------------------

Pre-built third party libraries bundled with this project
are not part of the Program covered by the GPL.
See libs/README-SDL.txt and libs/LICENSE-GLEW.txt for
more information on their licenses.

Fonts, models and textures in Data/ folder are not
part of the Program covered by the GPL. They are copyright
of their creators or released under other licenses.
See Data/README.txt for more information.
