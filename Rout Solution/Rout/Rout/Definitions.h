#pragma once

#pragma message("Building Definitions.h")


// Shortcut macros for resource directories
#define RESOURCE_DIR		L"../../res/"
#define CONFIG_DIR			RESOURCE_DIR L"config/"
#define FX_DIR				RESOURCE_DIR L"fx/"
#define IMAGES_DIR			RESOURCE_DIR L"img/"
#define LEVELS_DIR			RESOURCE_DIR L"levels/"
#define CONFIGFILE( x )		( CONFIG_DIR x )
#define EFFECT( x )			( FX_DIR x )
#define IMAGE( x )			( IMAGES_DIR x )
#define LEVEL( x )			( LEVELS_DIR x )
#define RED					1
#define BLUE				0

// GUI font definitions
#define EX_GUIFONT		L"Verdana"
#define EX_GUIFONTSIZE	18