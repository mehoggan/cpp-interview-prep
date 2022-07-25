cmake_minimum_required(VERSION 3.10)

project(InterviewQuestions)

include(./cmake/c++17.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Added in the order in which they are present in:
# https://bayergroupus.sharepoint.com/:w:/s/025530/EbdschEIvV9FkQIuRcTTOCsBPQFu
# 1HKKyzCfMF4L8u3blw?e=dQa219&wdOrigin=TEAMS-ELECTRON.p2p.bim&
# wdExp=TEAMS-CONTROL&wdhostclicktime=1652100732059
add_subdirectory("./TechnicalPhoneInterview")
add_subdirectory("./CSFundamentals")
add_subdirectory("./CodingScenario")
add_subdirectory("./CrackingTheCodingInterview")
