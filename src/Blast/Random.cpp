


#include <Blast/Random.hpp>

#include <algorithm>


static unsigned int basic_multiply_hash(std::string value)
{
   unsigned int result = 1;
   for (int i=0; i<value.size(); i++)
   {
      result *= (unsigned int)value[i];
   }
   return result;
}


namespace Blast
{
   Random::Random(unsigned int seed)
      : primary_seed(seed)
      , random_number_generator__for_get_random_int()
      , random_number_generator__for_get_random_bool()
      , random_number_generator__for_get_random_sign()
      , random_number_generator__for_get_random_float()
      , random_number_generator__for_get_random_double()
      , random_number_generator__for_get_one_in_chance()
      , random_number_generator__for_get_random_letter()
      , random_number_generator__for_get_random_letter_or_number()
      , random_number_generator__for_get_random_string()
      , random_number_generator__for_roll_dice()
      , random_number_generator__for_get_random_element()
      , random_number_generator__for_shuffle_elements()
      //, random_number_generator__for_get_random_color()
      //, random_number_generator__for_get_random_color_exhaustive()
      , shuffle_elements_seed_increment(0)
   {
      set_seed(primary_seed);
   }


   int Random::extract_random_int(int min, int max, std::mt19937 &rng)
   {
      int fixed_min = std::min(min, max);
      int fixed_max = std::max(min, max);
      int range = fixed_max - fixed_min + 1;
      return rng() % range + fixed_min;
   }


   unsigned char Random::extract_random_letter(bool lowercase, std::mt19937 &rng)
   {
      int num = extract_random_int(0, 26, rng);
      if (lowercase) return (unsigned char)(num%26 + 'a');
      return (unsigned char)(num%26 + 'A');
   }


   unsigned char Random::extract_random_letter_or_number(std::mt19937 &rng)
   {
      int num = extract_random_int(0, 10+26+26, rng); // 10 digits, 26 uppercase, 26 lowercase
      if (num <= 10) return (unsigned char)(num%10 + '0');
      else if ((num-10) <= 26) return (unsigned char)(num%26 + 'A');
      else if ((num-10-26) <= 26) return (unsigned char)(num%26 + 'a');
      return '-';
   }


   void Random::set_seed(unsigned int new_seed)
   {
      primary_seed = new_seed;

      // set the individual method seeds
      random_number_generator__for_get_random_int.seed(
            primary_seed + basic_multiply_hash("for_get_random_int")
         );
      random_number_generator__for_get_random_bool.seed(
            primary_seed + basic_multiply_hash("for_get_random_bool")
         );
      random_number_generator__for_get_random_sign.seed(
            primary_seed + basic_multiply_hash("for_get_random_sign")
         );
      random_number_generator__for_get_random_float.seed(
            primary_seed + basic_multiply_hash("for_get_random_float")
         );
      random_number_generator__for_get_random_double.seed(
            primary_seed + basic_multiply_hash("for_get_random_double")
         );
      random_number_generator__for_get_one_in_chance.seed(
            primary_seed + basic_multiply_hash("for_get_one_in_chance")
         );
      random_number_generator__for_get_random_letter.seed(
            primary_seed + basic_multiply_hash("for_get_random_letter")
         );
      random_number_generator__for_get_random_letter_or_number.seed(
            primary_seed + basic_multiply_hash("for_get_random_letter_or_number")
         );
      random_number_generator__for_get_random_string.seed(
            primary_seed + basic_multiply_hash("for_get_random_string")
         );
      random_number_generator__for_get_random_element.seed(
            primary_seed + basic_multiply_hash("for_get_random_element")
         );
      random_number_generator__for_shuffle_elements.seed(
            primary_seed + basic_multiply_hash("for_shuffle_elements")
         );
      shuffle_elements_seed_increment = 0;
      //std::mt19937 random_number_generator__for_get_random_color( // <- bug here in this declaration
            //primary_seed + basic_multiply_hash("for_get_random_color")
         //);
      //std::mt19937 random_number_generator__for_get_random_color_exhaustive( // <- bug here in this declaration
            //primary_seed + basic_multiply_hash("for_get_random_color_exhaustive")
         //);
   }




   unsigned int Random::get_seed()
   {
      return primary_seed;
   }




   bool Random::get_random_bool()
   {
      return random_number_generator__for_get_random_bool() % 2;
   }




   int Random::get_random_sign()
   {
      return (random_number_generator__for_get_random_sign() % 2) ? 1 : -1;
   }




   int Random::get_random_int(int min, int max)
   {
      std::mt19937 &rng = random_number_generator__for_get_random_int;
      //std::mt19937 &rng = random_number_generator;
      int fixed_min = std::min(min, max);
      int fixed_max = std::max(min, max);
      int range = fixed_max - fixed_min + 1;
      return rng() % range + fixed_min;
   }




   float Random::get_random_float(float min, float max)
   {
      std::mt19937 &rng = random_number_generator__for_get_random_float;
      float fixed_min = std::min(min, max);
      float fixed_max = std::max(min, max);
      float range = fixed_max - fixed_min;
      return (rng() / (float)rng.max()) * range + fixed_min;
   }




   double Random::get_random_double(double min, double max)
   {
      std::mt19937 &rng = random_number_generator__for_get_random_double;
      double fixed_min = std::min(min, max);
      double fixed_max = std::max(min, max);
      double range = fixed_max - fixed_min;
      return (rng() / (double)rng.max()) * range + fixed_min;
   }




   unsigned char Random::get_random_letter(bool lowercase)
   {
      std::mt19937 &rng = random_number_generator__for_get_random_letter;
      int num = extract_random_int(0, 26, rng);
      if (lowercase) return (unsigned char)(num%26 + 'a');
      return (unsigned char)(num%26 + 'A');
   }




   unsigned char Random::get_random_letter_or_number()
   {
      std::mt19937 &rng = random_number_generator__for_get_random_letter_or_number;
      int num = extract_random_int(0, 10+26+26, rng); // 10 digits, 26 uppercase, 26 lowercase
      if (num <= 10) return (unsigned char)(num%10 + '0');
      else if ((num-10) <= 26) return (unsigned char)(num%26 + 'A');
      else if ((num-10-26) <= 26) return (unsigned char)(num%26 + 'a');
      return '-';
   }




   std::string Random::get_random_string(unsigned int length)
   {
      std::mt19937 &rng = random_number_generator__for_get_random_string;
      std::string return_str;
      for (unsigned i=0; i<length; i++)
         return_str += extract_random_letter_or_number(rng);
      return return_str;
   }




   bool Random::get_one_in_chance(int chance)
   {
      std::mt19937 &rng = random_number_generator__for_get_one_in_chance;
      if (extract_random_int(0, chance - 1, rng) == 0)
         return true;
      return false;
   }




   int Random::roll_dice(int sides, int number_of_die)
   {
      std::mt19937 &rng = random_number_generator__for_roll_dice;
      int result = 0;
      for (int i = 0; i < number_of_die; i++)
         result += extract_random_int(sides, 1, rng);
      return result;
   }




   //ALLEGRO_COLOR Random::get_random_color()
   //{
      //std::mt19937 &rng = random_number_generator__for_get_random_color;
      //return color_palette[extract_random_int(0, color_palette.size(), rng)];
   //}




   // WARNING: TODO:
   // This function will not produce reliable random shuffles given a seed
   //ALLEGRO_COLOR Random::get_random_color_exhaustive()
   //{
      //static std::vector<ALLEGRO_COLOR> colors = color_palette;
      //static int next = colors.size();

      //std::mt19937 &rng = random_number_generator__for_get_random_color_exhaustive;

      //if (next >= (colors.size()-1))
      //{
         //std::shuffle(colors.begin(), colors.end(), rng);
         //next = 0;
      //}
      //else
      //{
         //next++;
      //}

      //return colors[next];
   //}



   //std::vector<ALLEGRO_COLOR> Random::get_source_color_palette()
   //{
      //return this->color_palette;
   //}
}


