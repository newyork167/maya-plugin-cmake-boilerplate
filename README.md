# Maya Plugin C++ CMake Boilerplate
This is a boilerplate for creating Maya plugins in C++. You will find various CMake Find* files (from @chadmv who I can't recommend enough! He has great repositories and his blog is full of great content) for finding not only Maya's devkit but other common libraries such as GLEW and Kinect. I'm hoping to add more boilerplates for different types of plugins. The next step I'm looking at getting setup is a basic plugin that allows you to jump into development making DAG and Shape plugins.

## Installation Requirements:
- [Maya](https://www.autodesk.com/products/maya/overview)
- [Maya devkit](https://help.autodesk.com/view/MAYAUL/2019/ENU/?guid=Maya_SDK_MERGED_Setting_up_your_build_html)
- [CMake](https://cmake.org/install/)
- I recommend:
  - [Visual Studio](https://visualstudio.microsoft.com/) / [Visual Code](https://code.visualstudio.com/) or [CLion](https://www.jetbrains.com/clion/) for Windows
  - Vim, [CLion](https://www.jetbrains.com/clion/) or [Code::Blocks](http://www.codeblocks.org/) for *nix
  - XCode or [CLion](https://www.jetbrains.com/clion/) for MacOS

Feel free to make pull requests or contact me on any social media platform @newyork167 if you think another CMake Find* file should be added or have any boilerplate additions that you feel would help make the base project better!

## Setup your CMakeLists.txt file
You will need to set the following variables in the CMakeLists.txt file
- MAYA_PLUGIN_OUTPUT_DIR => To a directory where you will load your custom Maya plugins. It is advised not to make this the plugins directory inside the Maya installation as the file/Maya can become corrupted
- MAYA_VERSION => Set this to the version of Maya you have installed and want to use the devkit of

## Running CMake
- For windows I suggest using either an IDE or the CMake GUI if you are new to CMake

- For *nix you can run the following for an in-place build (files are built in the same directory):

  ```
  cd maya-plugin-cmake-boilerplate
  ccmake .
  make
  ```

  or you can make a build directory and have the files output there

  ```
  cd maya-plugin-cmake-boilerplate
  mkdir build && cd build
  ccmake ../maya-plugin-cmake-boilerplate
  make
  ```

- For MacOS you can use the GUI installed with [brew](https://brew.sh/) ```brew cask install cmake``` (or if using port: ```port install cmake +gui```) and then build similar to *nix
  ```
  cd maya-plugin-cmake-boilerplate
  mkdir build && cd build
  cmake ../maya-plugin-cmake-boilerplate
  cmake --build .
  ```

## Credits
I've learned so much through these individuals in the past few months (amongst many others that I'm not remembering at the moment of course!)

@chadmv for the CMake find files and amazing online info!

@KostasAAA / [KostasAAA](https://twitter.com/KostasAAA) (Hopefully crediting the right github) for all his work on Twitter spreading information about graphics development.

[Hugo Guerra](https://twitter.com/HugoCGuerra) who through my constant annoyance of questions still takes the time to answer them and for introducing me to the notion of pipeline technical director as a potential career. He also has great VFX content for both artists and developers.