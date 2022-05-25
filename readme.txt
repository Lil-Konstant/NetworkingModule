How to integrate NetworkingModule (By Ronan Richardson) into your C++ Visual Studio project:

1. Download the NetworkingModule binary folder from GitHub at: https://github.com/Lil-Konstant/NetworkingModule (extract/unzip the folder once downloaded).
  Inside this folder is:
    - This readme.txt file detailing how to add the NetworkingModule to your C++ MCVS project.
    - The libraries required for the NetworkingModule, in the subfolder "libs"
    - The include header files required for the NetworkingModule, in the subfolder "include"
    - The Server.exe application that clients have been configured to connect to, run this before running client programs to connect
    - The libsndfile-1.dll and OpenAL32.dll files required for NetworkingModule applications to run, move these into your build/application directory for them to work
    
2. In your Solution Directory, create a folder called "dependencies", and drag and drop the unzipped NetworkingModule-main folder into it.
3. Within your Visual Studio project, go into the project properties (Project -> Properties), make sure the Platform is set to Win32 and Configuration is set to All.
4. Under VC++ Directories -> Include Directories, add the path of the NetworkingModule-main\include folder, $(SolutionDir)dependencies\NetworkingModule-main\include;
5. Under VC++ Directories -> Library Directories, add the path of the NetworkingModule-main\libs folder, $(SolutionDir)dependencies\NetworkingModule-main\libs;
6. Under Linker -> Input -> Additional Dependencies, change the configuration to Debug and add the following library names:
  Bootstrap_d.lib
  Raknet_d.lib
  Client_d.lib
  ws2_32.lib
7. Under Linker -> Input -> Additional Dependencies, change the configuration to Release and add the following library names:
  Bootstrap.lib
  Raknet.lib
  Client.lib
  ws2_32.lib
  
IMPORTANT: Don't forget to add the libsndfile-1.dll and OpenAL32.dll files to whatever build directory you choose, for both release and debug configs.
  
Your Visual Studio C++ project should now be configured to run and make use of the NetworkingModule.
Inherit your main game client from the public Client class to access the inbuilt networking capabilities.
