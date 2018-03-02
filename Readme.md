# Emp: a scriptable lighting calculation engine

I am not entirely sure how to describe this project... maybe as  *[Radiance](https://www.radiance-online.org/)
on steroids*; or maybe as a *higher level [Radiance](https://www.radiance-online.org/)*; or even as
*a less flexible [Radiance](https://www.radiance-online.org/)*. There is something
I am entirely sure, though: **This project intends to provide Radiance with all the capabilities
I have been wishing it had during the several years I have been using it**. That is:

* Efficient out-of-the-box multicore processing across programs (i.e. call several RTRACE or RCONTRIB
threads at the same time)
* Out of the box script optimization, eliminating redundant tasks (i.e. do not create two
octrees for calculating the Daylight Factor and the Annual Illuminance... one is enough...
but please reuse the ambient files when possible)
* Cross platform script-based model generation (i.e. do not rely on Unix programs to
generate complex geometry... on the contrary, allow including trigonometric functions,
randomness, and more, in all platforms)
* Read and write several file formats (i.e. allow me to draw my models in some modern
3D modelling tool)
* Simple automation of those tasks required on a daily basis, so I can work faster
and avoid errors (i.e. I do not want to write a script every time I want to perform a
Climate Based Daylight Simulation)
* Cross platform consistency (i.e. should I write `rcalc -e "$1 = $1+$2"` or
`rcalc -e '$1 = $1+$2'` ?)
* Workplane interpretation as geometry, not a grid of points (i.e. if I want to know
the Spatial Daylight Autonomy of a workplane, I can probably describe a polygon that
encolses it... but I do not want to write every point where the illuminance is measured)
* Post-processing capabilities (i.e. my workplane contains 4,528 sensors... I do not want
to know, nor write down, the illuminance of each of them on each of the 8,760 hours
of the year. Just return the CBD metric I asked for)
* Do not create 3,125 files, please (i.e. there are several files I am not interested in, which
are just intermediate results... please delete them afterwards)

Long story short, Emp is a (the first) wrapper to the [Emp_core](https://github.com/GroundhogLighting/emp_core)
library (yes... similar names. Please read the History section to understand why). In this case,
Emp provides the scripting capabilites (thanks to  [Lua](https://www.lua.org/))
and [Emp_core](https://github.com/GroundhogLighting/emp_core) provides the
calculations capabilities. **If you are only interested in [Emp_core](https://github.com/GroundhogLighting/emp_core),
feel free to fork it and create your own project... respecting the License.**

## Usage

Emp always receives two inputs: a **model** file and a **script** file. The former is meant
to provide a basis of geometry, materials, location, weather and other things; while the
latter is meant to perform actions and calculatons over this basis.

```bash
emp model script.lua [arguments]
```

An example of this could be

```bash
# that is, call RVU in this model, and see the view called "someView"

emp model.skp rvu someView

```

### The EMPATH

EMPATH is an environmental variable that keeps the Standard Scripts; that is, lua scripts that
are meant to be used on a daily basis. Setting the empath is as simple as:

```bash
# On Linux and macOS

export EMPATH=/some/directory/where/scripts/are/stored
```

```
# On windows
set EMPATH /some/directory/where/scripts/are/stored
```

This allows, for example, checking the information within a model by doing:

```bash
emp model getinfo # Note that the .lua is not strictly needed.
```

and the information regarding the number of layers, components, materials, views, workplanes
and more will be written to the standard output.


### Other uses

Other uses are meant to provide basic information
```bash

emp {--help|-h}        : prints this message
emp {--version|-v}        : prints version
emp {--about|-a}        : prints about
emp --checkpath        : prints the EMPATH variable
```


## Why Lua?

A reasonable question... A lot of people may tell you a lot about [Lua](https://www.lua.org/):
It is powerfull, small, fast, flexible, etc. However, in my opinion, I chose it because of two
reasons.

### It was meant to be embedded

The Lua C API is very well documented, easy to use and simple to implement... this does not
happen in all programming languages.

### It may be seen as plain text

People who are not familiar with programming languages may be affraid of reading scripts.
However, in the case of Lua, simple scripts may be seen as plain text files. Take, for example,
the case of the creation of the following plastic:

```
void plastic someId
0
0
5 0.7 0.05 0.05 0.05 0.05
```

Which in our Lua API is written as:

```lua
plastic {
    color = {0.7, 0.05, 0.05};
    specularity = 0.05;
    roughness = 0.05;
}

```

Even if I understand they are different, they can definetly be seen
as different alternatives to the same thing. This does not happen with all programming
languages eather.


## **A very simple model**: Radiance's "Scene 0" written in Lua language

Please notice that:

* The plastic material added is not asigned any name. Even if a name can be assigned (just like the light material),
Emp will assing a random ID as a name to it.
* Both materials added to the model are reused when creating geometrical elements.
This allows, for example, modifying the name of one of them very easily without breaking any
line of code below.
* Views are part of the model as well. Every model has some views that are nicer or more important
than others... and Emp tries to take this in consideration.
* Components can be created in the model, and instanced as many times as required, positioning
them in different places, and scaling them


```lua
-- =========
-- SCENE 0
-- =========

-- ADD GEOMETRY AND MATERIALS
-- ==========================

-- This is the material for my lightsource
bright = light {
    name = "bright";
    color = {100, 100, 100};
}

-- this is the material for my test ball:
red_plastic = plastic {
    color = {0.7, 0.05, 0.05};
    specularity = 0.05;
    roughness = 0.05;
}

-- here is the light source
sphere {
    center = {2, 1, 1.5};
    radius = 0.125;
    material = bright;
}

-- here is the ball
sphere {
    center = {0.7, 1.125, 0.625};
    radius = 0.125;
    material = red_plastic;
}

-- the wall material
gray_paint = plastic {
    name = "gray_paint";
    color = {0.5, 0.5, 0.5};
    specularity = 0;
    roughness = 0;
}

-- a box-shaped room
box {
    material = gray_paint;
    size = {3, 2, 1.75};
}

-- Material for a shiny blue box
blue_plastic = plastic {
    color = {0.1, 0.1, 0.6};
    specularity = 0.05;
    roughness = 0.1;
}

-- CREATE COMPONENTS
-- =================

the_box = component("box")

-- ADD GEOMETRY TO THEM
-- =====================

box {
    component  = the_box;
    material = blue_plastic;
    size = { 0.5, 0.5, 0.5}
}

-- INSTANCE THEM
-- ==============
instance {
    definition = the_box;
    position = {0.5, 0.75, 0};
    rz = 15;
}


-- ADD VIEWS
-- =========

view {
    name = "theView";
    position = {2.25, 0.375, 1};
    direction = {-0.25, 0.125, -0.125};
}
```
## **A very simple script**: Visualizing Radiance's "Scene 0"

We now have a model... how do we visualize it? EMPATH has a standard script called rvu.lua. It
allows calling RVU program easily, creating the necessary octrees, and deleting them afterwards.

```bash
# I know there is an rvu.lua file in the EMPATH directory
emp scene0.ghm rvu
```

Now... what is in the script file ?

```lua
-- rvu.lua

--Set the Auto Solve to false ... this will be explained later
auto_solve = false


-- Find a list of views in the model
views = get_views_list()

-- Try to find the given view...
-- Use the first argument given (i.e. argv[1]). If it does not exist, use the first view in the model
view_name = argv[1] or views[1]

-- Ensure that the view exist
if not is_view(view_name) then
    raise("View "..view_name.." does not exist") -- This will throw an error
end

-- Call the Radiance's RVU program
review(view_name)

```

Note that `rvu.lua` is a lua script should be stored in the EMPATH... otherwise, the call would be

```bash
# I know there is an rvu.lua file in the EMPATH directory
emp scene0.ghm ./full/path/to/rvu
```


## **Radiance, on steroids**: Sort of Radiance's "Scene 0", but with randomness


Lets see a bit of the good things of using a programming language instead of just text files and Unix files.

```lua
-- CREATE MATERIALS
-- ================

a_plastic = plastic {
    color = {0.6, 0.6, 0.6};
    specularity = 0.05;
    roughness = 0.01;
}

red_plastic = plastic {
    color = {0.7, 0.05, 0.05};
    specularity = 0.05;
    roughness = 0.05;
}

ground_material = plastic {
    color = {0.2, 0.2, 0.2};
    specularity = 0;
    roughness = 0;
}

-- ADD GROUND
-- ==========

ring {
    material = ground_material;
    center = {0,0,-5};
    direction = {0,0,1};
    inner_radius = 0;
    outer_radius = 20;
}

-- CREATE A COMPONENT
-- ==================

a_component = component("my_component")

sphere {
    component  = a_component;
    material = a_plastic;
    center = {-0.5, 0, 0};
    radius = 0.2;
}

sphere {
    component  = a_component;
    material = a_plastic;
    center = {0.5, 0, 0};
    radius = 0.2;
}

cylinder {
    component  = a_component;
    material = red_plastic;
    start = {-0.5, 0, 0};
    finish = {0.5, 0, 0};
    radius = 0.05;
}

-- ADD 50 RANDOM INSTANCES
-- =======================

for i=1,50 do
    instance {
        definition = a_component;
        position = {math.random()*10, math.random()*10, math.random()*10};
        rz = math.random()*360;
        rz = math.random()*360;
        ry = math.random()*360;
    }
end


-- ADD A VIEW
-- ===========

view {
    name = "theView";
    position = {15, 15, 15};
    direction = {-1, -1, -1};
}
```


![Random components image](https://drive.google.com/file/d/1ntj9bgcUca68M10m-kv20LkU0PACCWpQ/view?usp=sharing)

## A bit of history

*FULL DISCLAIMER: I am the developer of [Groundhog](http://www.groundhoglighting.com)*

After years of development, [Groundhog](http://www.groundhoglighting.com) has
become stable and intuitive enough to be used by industry, students and 
academics. However, the more intuitive and stable a tool is, the bigger
the projects it is used for. Indeed, what was once a tool used only for solving 
models with small rooms and few windows has become an excelent tool for
teaching students, who use it for much larger models with really complex
requirements (or so I have seen in my students exams).

Solving larger models force a tool to be much more time efficient (because no
one wants to wait 35 minutes for the results to come back). Even though
[Radiance](http://www.radiance-online.org) programs do their jobs as fast as they can
(and improving them is something this project is not yet focused in), an important fraction
of the time required to process a model was spent in reading and parsing files,
analizing numerical data, and performing, in series, several tasks that could be
easily paralellized. In other words, there was a lot of space for optimization.

Even if this project was initially meant to become the calculation engine behind
[Groundhog](http://www.groundhoglighting.com), it took me very little time to realize that
it had to be divided into [Emp_core](https://github.com/GroundhogLighting/emp_core),
which is an embeddable static library written in C++ that handles most calculations
and format translation; and several other wrappers meant to provide different users
with the capabilities of Emp_core. **This project, called Emp, is the first
implementation of an Emp_core wrapper**. It allows using  [Lua](https://www.lua.org/)
language for providing the capabilities mentioned in the first section.


## Origin of the name

Emp is not an acronym, but the short version of 'Empedocles'; who, according to Wikipedia:

>> ... is credited with the first comprehensive theory of light and vision. He put forward the idea that we see objects because light streams out of our eyes and touches them. 

Despite being wrong, this theory will sound highly familiar to anyone who has read about [Backward Ray-tracing](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) algorithms.

## Relevant Emp_core features

- **Cross-platform:** Emp is designed to work on Linux, macOS and Windows... although 
it has been tested only on one macOS and one Windows PC.
- **Radiance-based:** Thanks to [Radiance](http://www.radiance-online.org), Emp_core is
built upon years of experience, research and testing.
- **Capable of reading CAD formats:** Emp_core was designed in order to work directly from
different CAD files. SKB format is the only one supported for now.
- **Embeddable:** Written in C++, Emp_core can be embedded in several other tools.
- **Do not repeat processes:** Based on Groundhog's simulation manager, Emp_core
was provided with a Task-manager, which is able to understand several broad tasks (i.e. 
calculate Daylight Autonomy and Useful Daylight Illuminance) and eliminate redundant 
tasks (i.e. perform an annual simulation).
- **Parallel computing:** Thanks to [Intel Threading Building Blocks](https://github.com/01org/tbb),
Emp's Task Manager can schedule tasks and use parallel computing to leverage 
all the power in your machine and reduce calculation time.

## Important notice

So far, the SKP models that are read by Emp_core are meant to be created with Groundhog.
This is because a Groundhog model is a simple SKP model with metadata added to it, 
enabling Emp to understand what surface is 'real' and what surface is, for examaple,
a workplane.


## What is in the box

- README.md : This file
- premake5.lua : The [premake](https://premake.github.io/) script for building the project
- make.lua : Some scripts used only for pre-release tasks, such as documenting and others. 
It is used sort of like a make file
- main.h / main.cpp : The main header and source file
- main_test.h / main_test.cpp : The main and header files for running tests
- License.txt : The file with licensing information
- Doxyfile : The file used by Doxygen to generate the developer's documentation
- .gitmodules / .gitignore : Files used by Git version managing
- tests : Directory with automated tests (uses [Google Tests](https://github.com/google/googletest))
- standardscripts : Directory with standard scripts used as example and shipped with Emp for
performing common tasks
- src : The main directory with Emp's actual code
- prereleasescripts : lua scripts that are called by 'make.lua'
- premakescripts : lua scripts called before premake is called.
- guides : Directory with developer guidelines and specifications. They get documented in
the developer-doc
- googletest : Fork to [Google Tests](https://github.com/google/googletest), used for 
compiling and running tests.
- Emp-doc : The user documentation (i.e. API reference, standard script reference, tutorials, etc.). 
It is synced with the (Gitbook doc)[https://www.gitbook.com/book/groundhoglighting/Emp-doc/welcome]
- developer-doc : The developer documentation generated with Doxygen
- 3rdparty : Directory with external dependencies

## Building

Emp is intended to be cross-platform, thus we are using an automatic building tool. As Lua is the 
languange chosen to accompany C++ within Emp, it was natural to use premake5 (which is based on Lua)
as such tool. However, Emp uses [Intel's Threading Building Blocks]()https://github.com/01org/tbb 
(TBB) for allowing cross-platform parallel computing. Unfortunately, Intel TBB should be built using
make. So, for building you should:

### Build Intel TBB


### Create the project for your IDE

Emp is built using the simplest premake command... as mentioned in [Premake's documentation](https://github.com/premake/premake-core/wiki/Using-Premake):

> The simplest Premake command is:
>
>    premake5 [action]
> 
> Premake defines the following list of actions out of the box; projects may also add their own custom actions.
> 
> | Action      | Description                                       |
> |-------------|---------------------------------------------------|
> | vs2017      | Generate Visual Studio 2017 project files         |
> | vs2015      | Generate Visual Studio 2015 project files         |
> | vs2013      | Generate Visual Studio 2013 project files         |
> | vs2012      | Generate Visual Studio 2012 project files         |
> | vs2010      | Generate Visual Studio 2010 project files         |
> | vs2008      | Generate Visual Studio 2008 project files         |
> | vs2005      | Generate Visual Studio 2005 project files         |
> | gmake       | Generate GNU Makefiles (including [Cygwin][1] and [MinGW][2]) |
> | xcode4      | XCode projects (built-in [extension](https://github.com/premake/premake-core/tree/master/modules/xcode)) |
> | codelite    | CodeLite projects (built-in [extension](https://github.com/premake/premake-core/tree/master/modules/codelite)) |
> 
> To generate Visual Studio 2017 project files, use the command:
> 
>     premake5 vs2017
> 
> You can see a complete list of the actions and other options supported by a project with the command:
> 
>     premake5 --help
> 

### Edit and compile

Finally, you should edit and compile with whatever IDE or toolset you use.

## License

Copyright (C) 2017 Germán Molina (germolinal@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
