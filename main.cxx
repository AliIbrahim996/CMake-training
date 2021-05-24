#include<iostream>
#include<GLFW/glfw3.h>
#include<NewProConfig.h>
using namespace std;

int main(int argc, char* argv[]) {

    cout<<argv[0]<<"    Version "<<NewPro_VERSION_MAJOR
    <<"."<<NewPro_VERSION_MINOR<<endl;
	#ifdef USE_ADDER
    float a,b;
    cout<<"input two numbers\n";
    cin>>a>>b;
		cout << add(a, b) << "\n";
	#endif
   
    GLFWwindow *window;
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(300, 300, "Gears", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Draw gears
      //  draw();

        // Update animation
       // animate();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
