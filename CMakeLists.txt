cmake_minimum_required(VERSION 3.0)
project(miniTRUST CXX)

enable_testing()

set(TRUST_ROOT ${CMAKE_SOURCE_DIR})

add_definitions(-D_COMPILE_AVEC_GCC_)

add_subdirectory(src)

set(sub_parts
    obj_ThSol
    obj_chpdis
    obj_utilitaires
    obj_noyau
    obj_zvf
    obj_solv
    obj_champ
    obj_schtps
    obj_solvsys
    obj_ag
    obj_tmath
    obj_geom
    obj_op
    obj_noyaucl
    obj_main
    obj_solvdf
    obj_itsovdf
    obj_evalsovdf
    obj_sovdf_using_it_eval
    obj_chvdf
    obj_elmtvdf
    obj_zvdf
    obj_opvdf_diff_dift
    obj_opvdf_diff_dift_base
    obj_itvdf
    obj_evalvdf_diff_dift
    obj_evalvdf_divers
    obj_opvdf_divers
    obj_vdf
)

set(tgt_obj)
foreach(_bit ${sub_parts})
   set(tgt_obj ${tgt_obj} $<TARGET_OBJECTS:${_bit}>)
endforeach()

add_executable(miniTRUST ${tgt_obj})

