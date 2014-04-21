project "ResenseGame"
	kind "WindowedApp"
	language "C++"
	files { "./**.hh", "./**.h", "./**.c", "./**.cpp" }
   debugdir "../Dist"
   includedirs { 
      "./", 
      psybrusSDK .. "/Engine/Source/Shared/", 
      psybrusSDK .. "/Engine/Source/Platforms/Windows/"
   }

	-- External includes.
   includedirs { 
      psybrusSDK .. "/External/jsoncpp/include", 
      psybrusSDK .. "/External/portaudio/include",
      boostInclude
   }

	configuration "windows"
         libdirs {
            openal32LibPath
         }
   		links {
   			-- Windows libs.
   			"user32",
   			"gdi32",
   			"opengl32",
   			"winmm",
            "ws2_32",
            "IPHlpApi",
            "OpenAL32",

   			-- External libs.
            "External_portaudio",

   			-- Engine libs.
   			"Engine",
   		}
