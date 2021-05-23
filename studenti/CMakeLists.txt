if (MSVC)
    # warning level 4 
    add_compile_options(/W4)
else()
    # lots of warnings 
    add_compile_options(-Wall -Wextra -pedantic)
endif()
    

set(studenti
#anic
#bakotic
#barkovskiy
#basic
#bijelac
#blaskovic
#brajkovic
#calogovic
#cvetkovski
#dzafic
#fajdetic
#gasparini
#gizdulic
#grabar
#hajdin
#haramija
#illich
#janzetic
#jelusic
#jovanovic
#juricic
#karasin_stifter
#katalinic
#korlevic
#kozina
#lusetic
#majetic
#medur
mikulic
#milicevic
#negovetic
#ozbolt
#paro
#pekic
#putic
#rasetina
#sculac_luka
#sculac_robin
#sebelja
#sindija
#skrlj
#spehar
#subaric
#tus
#utmar
#versic
#vicevic
#vizintin
#vozila
#vukadin
#zagar
#zenzerovic
#zubcic_djurdjevic
)


foreach(subdir ${studenti})
    add_subdirectory(${subdir})
endforeach() 
