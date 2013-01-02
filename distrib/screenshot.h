
void TakeScreenshot(){
	char * buffer = new char[54 + 1024*768*3];

	char header[54] = {
		0x42,0x4D,0x36,0x00,0x24,0x00,0x00,0x00,
		0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
		0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x03,
		0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0xC4,0x0E,
		0x00,0x00,0xC4,0x0E,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00
	};
	for(int i=0; i<54;i++) buffer[i] = header[i];
	*(int*)&(buffer[0x22]) = 1024*768*3;
	*(int*)&(buffer[0x12]) = 1024;
	*(int*)&(buffer[0x16]) = 768;

	glReadPixels(0,0,1024,768, GL_BGR, GL_UNSIGNED_BYTE, buffer+54);
	
	FILE * file = fopen("screenshot.bmp", "wb");
	fwrite(buffer, 54+1024*768*3, 1, file);
	fclose(file);

};

double Zero(){
	return 0.0;
}

void callGlfwOpenWindowHint(int target, int hint){
	if ( target == GLFW_FSAA_SAMPLES )
		return; // Disable MSAA when testing, since this is the biggest source of errors
	glfwOpenWindowHint(target, hint);
}


#define glfwSwapBuffers() TakeScreenshot(); break;
#define glfwGetTime() Zero()
#define glfwOpenWindowHint(a,b) callGlfwOpenWindowHint(a,b)
