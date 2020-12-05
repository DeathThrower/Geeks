#include "ActionAddNotes.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <fstream>
ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{
}

bool ActionAddNotes::Execute()
{
	string notesFile = "Notes.txt"; // notesFile Path
	string notepadPath = "notepad \"" + notesFile + "\""; // Notepad opening command
	if (!ifstream(notesFile)) { // Checks if the file already exists
		ofstream file(notesFile); // if not exists create file named Notes.txt
		file.close(); // close the file to be able to edit it by the user 
	}
	system(notepadPath.c_str()); // Excute notepad command
	return true; // Fucntion return true to ensure it works correctly
}


ActionAddNotes::~ActionAddNotes()
{
}
