subdir('ActorGraph')
subdir('Node')



Actor_files = files(['Actor.cpp', 'Actor.hpp'])
Actor_includes = include_directories('.')
Actor_lib = library('Actor', sources: Actor_files,dependencies :[ActorNode_dep, MovieNode_dep,edge_dep])
Actor_dep = declare_dependency(include_directories: Actor_includes,
   link_with: Actor_lib)

ActorGraph_lib = library('ActorGraph', sources: ActorGraph_files,dependencies :[ActorNode_dep, MovieNode_dep,Actor_dep,edge_dep])
ActorGraph_dep = declare_dependency(include_directories: ActorGraph_includes,
   link_with: ActorGraph_lib)

DisjointSet_files = files(['DisjointSet.cpp', 'DisjointSet.hpp'])
DisjointSet_includes = include_directories('.')
DisjointSet_lib = library('DisjointSet', sources: DisjointSet_files,dependencies :[ActorNode_dep, MovieNode_dep,edge_dep,Actor_dep])
DisjointSet_dep = declare_dependency(include_directories: DisjointSet_includes,
   link_with: DisjointSet_lib)


pathfinder_exe = executable('pathfinder.cpp.executable', 
    sources: ['pathfinder.cpp'],
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep,Actor_dep,edge_dep,cxxopts_dep,DisjointSet_dep],
    install : true)


linkpredictor_exe = executable('linkpredictor.cpp.executable', 
    sources: ['linkpredictor.cpp'],
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep,Actor_dep,edge_dep,cxxopts_dep],
    install : true)

movietraveler_exe = executable('movietraveler.cpp.executable', 
    sources: ['movietraveler.cpp'],
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep,Actor_dep,edge_dep,cxxopts_dep,DisjointSet_dep],
    install : true)