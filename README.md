

# shaders folder (from shaders archive) shoud be in C:\\dev
# Dependencies folder (from Dependencies archive) should be in solution directory
 The program can be compiled in Visual Studio  
 Visual Studio project properties:  
 Default (empty) project  
 Configuration: Debug
 Platform: Win32
 1)C/C++ -- General -- additional include directories
 $(ProjectDir)Dependencies\GLFW\include;$(ProjectDir)Dependencies\GLEW\include  
   
 2)C/C++ -- Preprocessor -- preprocessor definitions
 GLEW_STATIC;_MBCS;%(PreprocessorDefinitions)
   
 3)Linker -- General -- additional library directoies
 $(ProjectDir)Dependencies\GLFW\lib-vc2019;$(ProjectDir)Dependencies\GLEW\lib\Release\Win32  
   
 4)Linker -- Input -- additional dependencies 
 glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib;glew32s.lib;winmm.lib

  
