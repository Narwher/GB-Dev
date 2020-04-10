# Homebrew Software on the Nintendo Game Boy with GBDK

Thanks to [GBDK](http://gbdk.sourceforge.net/), software can be written for the Nintendo Game Boy in the C language, instead of nasty gbZ80 assembler language. 

## Why make software on the Game Boy..?

I've always been fascinated with the high output of quality games on Nintendo's 1989 handheld. With such underpowered hardware specs, it's remarkable how much talented developers could squeeze out of the restraints. When it comes to creating art of any medium, I enjoy working with limitations. It forces you to think differently and seek unique approaches as to how to get desired results, pushing your wits as well as the given resources to their limit. This concept is the basis of all innovation.

Plus, I just like the Game Boy. It's cumbersome yet built like a tank; homely to the eye with its blurry pea-green screen yet oddly stylish. And you gotta love that stereo™ chiptune music!

## Goals of this project

This project will serve two purposes - to make ***frickin' awesome*** homebrew software for the Game Boy, as well as to further my knowledge and application of the C language.

First, I will learn the basics of GB programming. The software in the 'test' folder follows Videlais' [GBDK Tutorial](https://videlais.com/2016/07/03/programming-game-boy-games-using-gbdk-part-1-configuring-programming-and-compiling/). 

I intend to create at least two pieces of software by July 2020:
1. A port - most likely of a simple, roguelike dungeon crawler - most likely one of small size like flends's [zigClimb](http://flend.net/zigclimb/)
2. An original game of short-medium length. I'm interesting in genres like platforming/adventure. A visual novel is also well within scope.

These will be kept track of in the [projects section](https://github.com/Narwher/GB-Dev/projects) (soon to be populated)

## How to build
First, the [GBDK](http://gbdk.sourceforge.net/) must be downloaded and installed to the host system. Within the **(Project Name)/src** folder is a **build.bat** script that compiles the source into a .gb file (the most common extension for Game Boy binaries). 

## How to play
Game Boy binary files can be played on actual hardware via aftermarked flash memory cartridges. Simply copy the .gb file to an microSD card --> Flash cartridge, select the file and play! 

.gb files can also be played on many platforms via emulation software (one of which is provided in the **emulation** folder. The Game Boy is emulated almost perfectly on just about every platform that runs software! This allows for a wide user-base and portability for your software. It's a simple as running the emulator, selecting the .gb file via the file menu, and you're done.

## Conclusion
That's all folks!!!
