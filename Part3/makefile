files: sem host 

sem: sem.h
	gcc -o sem sem.h -pthread

host: host.c
	gcc -o host host.c -pthread

	@echo compilation is successful

clean: 
	@rm sem host
	@echo compiled files are cleaned
