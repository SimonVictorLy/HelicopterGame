
OPEN_GL = -lGLU -lGL -lglut 	# include all OpenGl libraries
default:
	g++ -o runfile *.cpp $(OPEN_GL) 
