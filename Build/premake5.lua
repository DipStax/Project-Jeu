workspace "Project-Jeu"
	location ".."
	configurations "Debug"
	startproject "Client"
	
	project "Client"
		kind "ConsoleApp"
		language "C++"
		location "../Client/"
		files {	"../Client/Client/src/**.cpp",
				"../Client/Client/include/**.h",
				"../Client/Client/include/**.inl" }
		defines "SFML_STATIC"
		libdirs "../Lib/SFML-2.5.1/lib"
		links {	"sfml-graphics-s-d.lib", "sfml-window-s-d.lib",
				"sfml-audio-s-d.lib", "sfml-network-s-d.lib",
				"sfml-system-s-d.lib", "opengl32.lib",
				"freetype.lib", "winmm.lib",
				"gdi32.lib", "openal32.lib",
				"flac.lib", "vorbisenc.lib",
				"vorbisfile.lib", "vorbis.lib",
				"ogg.lib", "ws2_32.lib" }
		includedirs { "../Lib/SFML-2.5.1/include", "../Client/Client/include" }
		filter "configurations:Debug"
			defines "DEBUG"
			symbols "on"
			
	project "Serveur_Master"
		kind "ConsoleApp"
		language "C++"
		location "../Serveur_Master"
		files { "../Serveur_Master/Serveur_Master/src/**.cpp",
				"../Serveur_Master/Serveur_Master/include/**.h",
				"../Serveur_Master/Serveur_Master/include/**.inl" }
		defines "SFML_STATIC"
		libdirs "../Lib/SFML-2.5.1/lib"
		links {	"sfml-graphics-s-d.lib", "sfml-window-s-d.lib",
				"sfml-audio-s-d.lib", "sfml-network-s-d.lib",
				"sfml-system-s-d.lib", "opengl32.lib",
				"freetype.lib", "winmm.lib",
				"gdi32.lib", "openal32.lib",
				"flac.lib", "vorbisenc.lib",
				"vorbisfile.lib", "vorbis.lib",
				"ogg.lib", "ws2_32.lib" }
		includedirs { "../Lib/SFML-2.5.1/include", "../Serveur_Master/Serveur_Master/include" }
		filter "configurations:Debug"
			defines "DEBUG"
			symbols "on"
			
	project "Serveur_User"
		kind "ConsoleApp"
		language "C++"
		location "../Serveur_User"
		files { "../Serveur_User/Serveur_User/src/**.cpp",
				"../Serveur_User/Serveur_User/include/**.h",
				"../Serveur_User/Serveur_User/include/**.inl" }
		defines "SFML_STATIC"
		libdirs { "../Lib/SFML-2.5.1/lib", "../Lib/Sqlite3" }
		links {	"sfml-graphics-s-d.lib", "sfml-window-s-d.lib",
				"sfml-audio-s-d.lib", "sfml-network-s-d.lib",
				"sfml-system-s-d.lib", "opengl32.lib",
				"freetype.lib", "winmm.lib",
				"gdi32.lib", "openal32.lib",
				"flac.lib", "vorbisenc.lib",
				"vorbisfile.lib", "vorbis.lib",
				"ogg.lib", "ws2_32.lib",
				"sqlite3.lib" }
		includedirs { "../Lib/SFML-2.5.1/include",
					  "../Serveur_User/Serveur_User/include",
					  "../Lib/Json",
					  "../Lib/Sqlite3" }
		filter "configurations:Debug"
			defines "DEBUG"
			symbols "on"