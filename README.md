Zenom MCU Target
====================================

This is a target of Zenom real time platform.
It is mainly targeted to micro controller units.
Code is under development. There is no real MCU target.
It is simulated under Linux. 
It is planned that in the feature code will be ported to STM32F0 MCU

Howto
==================================

In order to generate C code of proto messages one needs Nanopb project. 
After obtainin Nanopb project, run make under nanopb/genarator/proto and
copy 'nanopb/generator/proto/' 'nanopb/generator/nanopb_generator.py' 'nanopb/generator/protoc-gen-nanopb'  to '/usr/local/bin'
Make will automatically generate necessary C files for proto message definition.

