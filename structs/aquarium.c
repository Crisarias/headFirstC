#include <stdio.h>

struct exercise {
  const char *description;
  float duration;
};

struct meal {
  const char *ingredients;
  float weight;
};

struct preferences {
  struct meal food;
  struct exercise exercise;
};

struct fish {
  const char *name;
  const char *species;
  int teeth;
  int age;
  struct preferences care;
};

void label(struct fish f)
{
  printf("Name: \n",f.name);
  printf("Species: \n",f.species);
  printf("Food ingredients: \n",f.care.food.weight);
  printf("Food weight: \n",f.care.food.weight);
  printf("Exercise description: \n",f.care.exercise.description);
  printf("Exercise duration: \n",f.care.exercise.duration);
}


int main(int argc, char const *argv[])
{
    struct fish snappy = {"Snappy","Piranha",69,4,{{"meaat",0.2},{"swim in the jacuzzi"}, 7.5}};
    return 0;
}
