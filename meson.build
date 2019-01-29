project('my-youtube-client', 'cpp',
	default_options : ['cpp_std=c++17'])

# DEPENDENCIES
curl = dependency('libcurl')
rapidjson = dependency('RapidJSON')


# EXTRA COMPILE OPTIONS
if get_option('buildtype').startswith('debug')
  add_project_arguments('-Wall', '-Wextra', '-Werror', '-DFORTIFY_SOURCE=1',
			'-ggdb3',
			language : 'cpp')
endif
# elif get_option('buildtype') == 'release'
#   add_project_arguments('-DNDEBUG', '-O3', '-s',
#   			language : 'cpp')
# endif

# SOURCES
sources = ['main.cpp',
	   'Config.cpp',
	   'CURLcontext.cpp',
	   'SearchResponse.cpp',
	   'Operation.cpp',
	   'SearchOperation.cpp']

incl = include_directories('.')

# BINARIES
executable('yt', sources : sources,
	   include_directories : incl,
	   dependencies : [curl, rapidjson],
	  )
