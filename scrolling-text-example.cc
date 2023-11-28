// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to scroll text.
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

// For a utility with a few more features see
// ../utils/text-scroller.cc

#include "led-matrix.h"
#include "graphics.h"

#include <string>

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace rgb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static int usage(const char *progname) {
  fprintf(stderr, "usage: %s [options] <text>\n", progname);
  fprintf(stderr, "Takes text and scrolls it with speed -s\n");
  fprintf(stderr, "Options:\n");
  fprintf(stderr,
          "\t-s <speed>        : Approximate letters per second. "
          "(Zero for no scrolling)\n"
          "\t-l <loop-count>   : Number of loops through the text. "
          "-1 for endless (default)\n"
          "\t-f <font-file>    : Use given font.\n"
          "\t-x <x-origin>     : X-Origin of displaying text (Default: 0)\n"
          "\t-y <y-origin>     : Y-Origin of displaying text (Default: 0)\n"
          "\t-t <track=spacing>: Spacing pixels between letters (Default: 0)\n"
          "\n"
          "\t-C <r,g,b>        : Text-Color. Default 255,255,0\n"
          "\t-B <r,g,b>        : Background-Color. Default 0,0,0\n"
          "\n"
          );
  rgb_matrix::PrintMatrixFlags(stderr);
  return 1;
}

static bool parseColor(Color *c, const char *str) {
  return sscanf(str, "%hhu,%hhu,%hhu", &c->r, &c->g, &c->b) == 3;
}

static bool FullSaturation(const Color &c) {
  return (c.r == 0 || c.r == 255)
    && (c.g == 0 || c.g == 255)
    && (c.b == 0 || c.b == 255);
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;
  if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv,
                                         &matrix_options, &runtime_opt)) {
    return usage(argv[0]);
  }

  Color color(255, 255, 0);
  Color bg_color(0, 0, 0);
   // Read the color information from the "color.txt" file.
  FILE* color_file = fopen("/home/admin/rpi-rgb-led-matrix/examples-api-use/color_text.txt", "r");
  if (color_file == NULL) {
    fprintf(stderr, "Error: Unable to open color file 'color.txt'\n");
    return 1;
  }

  int color_number;
  if (fscanf(color_file, "%d", &color_number) != 1) {
    fprintf(stderr, "Error: Unable to read color information from file 'color.txt'\n");
    printf("color code: %d",color_number);
    fclose(color_file);
    return 1;
  }

  fclose(color_file);

  if (color_number == 1) {
    color = Color(255, 0, 0); // Red
  } else if (color_number == 2) {
    color = Color(0, 255, 0); // Green
  } else if (color_number == 3) {
    color = Color(0, 0, 255); // Blue
  } else {
    fprintf(stderr, "Error: Invalid color number in file 'color.txt'\n");
    return 1;
  }
    //Color color(r1, g1, b1);

  //const char *bdf_font_file = NULL;
  //std::string line;
  /* x_origin is set by default just right of the screen */
  const int x_default_start = (matrix_options.chain_length
                               * matrix_options.cols) + 5;
  int x_orig = x_default_start;
  int y_orig = 0;
  int letter_spacing = 0;
  float speed = 7.0f;
  int loops = -1;
  int flag = 0;
  char content[10];
  char bdf_font_file[256];

  int opt;
  while ((opt = getopt(argc, argv, "x:y:f:C:B:t:s:l:")) != -1) {
    switch (opt) {
    case 's': speed = atof(optarg); break;
    case 'l': //loops = atoi(optarg); 
           

    break;
    case 'x': x_orig = atoi(optarg); break;
    case 'y': y_orig = atoi(optarg); break;
   // case 'f': bdf_font_file = strdup(optarg); break;
    case 't': letter_spacing = atoi(optarg); break;
    case 'C':
      if (!parseColor(&color, optarg)) {
        fprintf(stderr, "Invalid color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      break;
    case 'B':
      if (!parseColor(&bg_color, optarg)) {
        fprintf(stderr, "Invalid background color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      break;
    default:
      return usage(argv[0]);
    }
  }
  
   FILE* font_file_ptr = fopen("/home/admin/rpi-rgb-led-matrix/examples-api-use/font_file.txt", "r");
    if (!font_file_ptr) {
        fprintf(stderr, "Failed to open the font file.\n");
        return 1;
        
    }
    
    //if (bdf_font_file == NULL) {
    //fprintf(stderr, "Need to specify BDF font-file with -f\n");
    //return usage(argv[0]);
  //}
    
    if (fgets(bdf_font_file, sizeof(bdf_font_file), font_file_ptr)) {
        // Remove the newline character, if present.
        char* newline = strchr(bdf_font_file, '\n');
        if (newline)
            *newline = '\0';
    } else {
        fprintf(stderr, "Failed to read font file name.\n");
        fclose(font_file_ptr);
        return 1;
    }
        

    // Close the font file name file.
    fclose(font_file_ptr);
    
    
  
  

  FILE* input_file = fopen("/home/admin/rpi-rgb-led-matrix/examples-api-use/rgb_text.txt", "r"); // Replace with the path to your text file.
  
  if (!input_file) {
    fprintf(stderr, "Failed to open the input file.\n");
    
    return 1;
  }
  // Read the text from the file and store it in 'line'.
  char line[25];
  if (!fgets(line, sizeof(line), input_file)) {
    fprintf(stderr, "Failed to read from the input file.\n");
    fclose(input_file);
    int line_length = strlen(line);
    line[line_length - 1] = ' ';
    return 1;
  }
    fclose(input_file);

  

  
  
    
  
  
  

  /*
   * Load font. This needs to be a filename with a bdf bitmap font.
   */
  rgb_matrix::Font font;
  if (!font.LoadFont(bdf_font_file)) {
    fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
    return 1;
  }

  RGBMatrix *canvas = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
  if (canvas == NULL)
    return 1;

  const bool all_extreme_colors = (matrix_options.brightness == 100)
    && FullSaturation(color)
    && FullSaturation(bg_color);
  if (all_extreme_colors)
    canvas->SetPWMBits(1);

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  printf("CTRL-C for exit.\n");

  // Create a new canvas to be used with led_matrix_swap_on_vsync
  FrameCanvas *offscreen_canvas = canvas->CreateFrameCanvas();

  int delay_speed_usec = 1000000;
  if (speed > 0) {
    delay_speed_usec = 1000000 / speed / font.CharacterWidth('W');
     

    
  } else if (x_orig == x_default_start) {
    // There would be no scrolling, so text would never appear. Move to front.
    x_orig = 0;
  }

  int x = x_orig;
  int y = y_orig;
  int length = 0;
  
  
   //flag = 1;   
  //while(flag)
    //{   
        
        //FILE *fptr = fopen("/home/admin/rpi-rgb-led-matrix/examples-api-use/switch.txt", "r");
        
        //if (fgets(content, sizeof(content), fptr) != NULL) {
          //content[strcspn(content,"\n")] = '\0';
          
          ////fprintf(stderr,"-%s-",content);
            
            //if (strncmp(content, "stop",4) == 0) {
                
                //flag = 0;
                //delete canvas;
            //}
            //else { 
             //fprintf(stderr, "\n no stop recieved %s",content); }
        //}

        //fclose(fptr);
        //sleep(1);
        ////delete canvas;
    //}



  while (!interrupt_received && loops != 0) {
   

    offscreen_canvas->Fill(bg_color.r, bg_color.g, bg_color.b);
    // length = holds how many pixels our text takes up
    length = rgb_matrix::DrawText(offscreen_canvas, font,
                                  x, y + font.baseline(),
                                  color, nullptr,
                                  line, letter_spacing);
    

    if (speed > 0 && --x + length < 0) {
      x = x_orig;
      if (loops > 0) --loops;
    }

    // Swap the offscreen_canvas with canvas on vsync, avoids flickering
    offscreen_canvas = canvas->SwapOnVSync(offscreen_canvas);
    usleep(delay_speed_usec);
    
    FILE *fptr = fopen("/home/admin/rpi-rgb-led-matrix/examples-api-use/switch.txt", "r");
        if (fgets(content, sizeof(content), fptr) != NULL) {
          content[strcspn(content,"\n")] = '\0';
        //fprintf(stderr,"-%s-",content);
            if (strncmp(content, "stop",4) == 0) {
                flag = 0;
                delete canvas;
            }
            else { 
             fprintf(stderr, "\n no stop recieved %s",content); }
        }

        fclose(fptr);
    
  }
 

  // Finished. Shut down the RGB matrix.
  delete canvas;

  return 0;
}
