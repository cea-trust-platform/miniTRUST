file(GLOB srcs [A-Z|a-z]*.cpp [A-Z|a-z]*.c [A-Z|a-z]*.f)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}  ${TRUST_ROOT}/include/backward  ${TRUST_ROOT}/src/Kernel/Champs  ${TRUST_ROOT}/src/Kernel/Champs_dis  ${TRUST_ROOT}/src/Kernel/Cond_Lim  ${TRUST_ROOT}/src/Kernel/Framework  ${TRUST_ROOT}/src/Kernel/Geometrie  ${TRUST_ROOT}/src/Kernel/Math  ${TRUST_ROOT}/src/Kernel/Math/Matrices  ${TRUST_ROOT}/src/Kernel/Math/SolvSys  ${TRUST_ROOT}/src/Kernel/Operateurs  ${TRUST_ROOT}/src/Kernel/Utilitaires  ${TRUST_ROOT}/src/Kernel/VF/Zones  ${TRUST_ROOT}/src/ThHyd/Incompressible/Cond_Lim  ${TRUST_ROOT}/src/ThHyd/Modele_turbulence_base  ${TRUST_ROOT}/src/ThHyd/Turbulence  ${TRUST_ROOT}/src/ThHyd/Incompressible/Equations  ${TRUST_ROOT}/src/ThSol  ${TRUST_ROOT}/src/VDF  ${TRUST_ROOT}/src/VDF/Champs  ${TRUST_ROOT}/src/VDF/Cond_Lim  ${TRUST_ROOT}/src/VDF/Zones  ${TRUST_ROOT}/src/VDF/Operateurs/Iterateurs     ${TRUST_ROOT}/src/VDF/Operateurs/Eval_Diff_Dift     ${TRUST_ROOT}/src/VDF/Operateurs/Eval_Divers     ${TRUST_ROOT}/src/VDF/Operateurs/Op_Conv     ${TRUST_ROOT}/src/VDF/Operateurs/Op_Diff_Dift/Op_Diff_Dift_base     ${TRUST_ROOT}/src/VDF/Operateurs/Op_Divers)
add_library(obj_opvdf_diff_dift OBJECT  ${srcs} )
set(listlibs ${listlibs} opvdf_diff_dift PARENT_SCOPE    )
#add_custom_target(check_sources_opvdf_diff_dift   COMMAND check_sources.sh ${CMAKE_CURRENT_SOURCE_DIR} ) #COMMENT  "checking code validity opvdf_diff_dift" )
#add_DEPENDENCIES(obj_opvdf_diff_dift check_sources_opvdf_diff_dift)
if(COMPIL_DYN)
  add_library(opvdf_diff_dift SHARED   $<TARGET_OBJECTS:obj_opvdf_diff_dift> )
  install(TARGETS opvdf_diff_dift  DESTINATION lib)
endif(COMPIL_DYN)
