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




pathfinder_exe = executable('pathfinder.cpp.executable', 
    sources: ['pathfinder.cpp'],
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep,Actor_dep,edge_dep,cxxopts_dep],
    install : true)


linkpredictor_exe = executable('linkpredictor.cpp.executable', 
    sources: ['linkpredictor.cpp'],
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep,Actor_dep,edge_dep,cxxopts_dep],
    install : true)