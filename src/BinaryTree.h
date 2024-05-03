#pragma once
#include "TNode.h"
#include <deque>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <string>
template <typename T>

class BinaryTree
{
public:
	TNode<T>* head;

public:
	BinaryTree(const std::initializer_list<T>& values)
	{
		//convert values to deque

		std::deque<T> values_as_deque(values);

		//the reason we are using 2 checks to see if
		//deque is greater than 0
		//is because we want to initialize the head if there
		//is at least 1 value
		//we cant check if size > 2 to run everything
		//or else the head won't get initializied with the value

		if(values_as_deque.size() > 0)
		{
			head = new TNode<T>;
			head->data = values_as_deque.front();
			values_as_deque.pop_front();
		}

		if(values_as_deque.size() > 0)
			SatiateTree(head, values_as_deque);
	}

	//where func is what you're printing as a string
	void PrintTreeFull(std::function<std::string(T)>& func)
	{
		//details of the tree we need to know
		int num_layers = 0;
		int max_string_length = 0;

		GetNumLayers(head, num_layers);
		GetMaxStringLength(head, max_string_length, func);

		int gap_size = max_string_length + 2;
		char padding_char = '_';

		PrintSettings settings(padding_char, gap_size, num_layers, max_string_length, func);
		std::vector<std::string> lines;

		//2 lines per layer
		//last layer doesn't contain any children
		//so no branch characters (/\)
		lines.resize(num_layers * 2 - 1);
		PrintTreeRaw(this->head, settings, lines);

		for(const auto& line : lines)
		{
			std::cout << line << std::endl;
		}
	}

private:
    struct PrintSettings
    {
        char padding_char;
        int gap_size;
        int num_layers;
        int max_string_length;
        std::function<std::string(T)>& func;

        PrintSettings(char pad, int gap, int layers, int str_len, std::function<std::string(T)>& f)
            : padding_char(pad)
              , gap_size(gap)
              , num_layers(layers)
              , max_string_length(str_len)
              , func(f)
        { }
    };

	void PrintTreeRaw(const TNode<T>* const node,
					  const PrintSettings& settings,
					  std::vector<std::string>& lines,
					  int cur_depth = 0)
	{
		//cur_depth begins at 0
		//whereas num_layers' lowest val is 1
		//so to check if lowest depth
		//must do cur_depth >= num_layers - 1

		if(!node)
			return;

		std::string value = settings.func(node->data);

		//This whole secion basically boils down:
		//making the values the same length.

		/****************************************************************************/
		int num_value_pad = settings.max_string_length - value.length();

		int num_sub_value_pad = num_value_pad / 2;
		if(num_value_pad % 2 == 0)
		{
			std::string sub_value_pad(num_sub_value_pad, '_');
			value = sub_value_pad + value + sub_value_pad;
		}
		else
		{

			std::string sub_value_pad1(num_sub_value_pad, '_');
			std::string sub_value_pad2(num_sub_value_pad + 1, '_');
			value = sub_value_pad1 + value + sub_value_pad2;
		}
		/****************************************************************************/

		//the index of the lines vector is 2*cur_depth
		//because one depth takes 2 lines to draw branch chars
		int line_depth = cur_depth * 2;

		//pad_depth is what our GetPadding() takes
		//it runs backwards to our cur_depth and is
		//[1, num_layers] whereas cur_depth = [0, num_layers - 1]
		//note this 1 is normalized to a zero in our GetPadding()
		//higher the number the more the padding
		int pad_depth = settings.num_layers - cur_depth;

		//initializing variables used for drawing

		/****************************************************************************/
		int num_spaces_before_padding = 0;
		std::string spaces_before_padding = "";

		//padding won't change depending on draw state
		//it can be 0
		int num_padding = getPadding(settings, pad_depth);
		std::string padding = "";

		int num_spaces_before_slash = 0;
		std::string spaces_before_slash = "";

		int num_spaces_after_slash = 0;
		std::string spaces_after_slash = "";
		/****************************************************************************/

		int gap_between_nodes = GetNodeDistance(settings, cur_depth);
		bool has_padding = num_padding > 0;

		//nodes exist we must calculate for
		//the node offset
		bool nodes_exist = !lines[line_depth].empty();
		if(nodes_exist)
		{
			/* cursor will start at the end of prev nodes' padding
                   spaces before we can start drawing the padding -
                   is to be the gap between these nodes subtracted by both paddings'
                   this is to account for the cursor position
                        
                        cursor here         needs to be here
                    _1_/                    \_1_
                   /   \                    /   \

                 gap between nodes is the distance between the 1's in this case

                                                                                          */
			num_spaces_before_padding = gap_between_nodes - (2 * num_padding);

			/*
                num_spaces_before_padding is now the distance between the
                end of the first nodes' padding to the start of the next nodes'
                padding

                         cursor here       needs to be here
                    _1_  /                 \ _1_
                   /   \/                  \/   \

                therefore we must subtract 2 from num_spaces_before_padding
                because the slash will be drawn a character before the padding
                and the cursor begins at the end of the first nodes' slash

                                                                        */
			num_spaces_before_slash = num_spaces_before_padding - 2;
		}
		else
		{
			//No nodes in line, calculate default spacing
			num_spaces_before_padding = getPadding(settings, pad_depth + 1) - num_padding;
			num_spaces_before_slash = num_spaces_before_padding - 1;
		}

		//spaces after slash is independent of node-offset
		num_spaces_after_slash = num_padding + settings.max_string_length + num_padding;

		bool isLastLayer = cur_depth >= settings.num_layers - 1;

		//if we're printing the last layer
		//we don't have to worry about printing branches
		//and the gap_size is a known constant
		if(isLastLayer)
		{
			//if there are children, we must offset the value
			//by the gap size
			int num_offset = 0;
			if(nodes_exist)
				num_offset = settings.gap_size;

			std::string offset(num_offset, ' ');

			lines[line_depth] += offset + value;
		}
		else //printing any other layer
		{
			//initialize the strings with the values
			padding = std::string(num_padding, '_');
			spaces_before_padding = std::string(num_spaces_before_padding, ' ');
			spaces_before_slash = std::string(num_spaces_before_slash, ' ');
			spaces_after_slash = std::string(num_spaces_after_slash, ' ');

			//draw the character and padding
			lines[line_depth] += spaces_before_padding + padding + value + padding;

			//draw the branch slashes
			lines[line_depth + 1] += spaces_before_slash + "/" + spaces_after_slash + "\\";
		}

		//print the rest of the tree
		PrintTreeRaw(node->left, settings, lines, cur_depth + 1);
		PrintTreeRaw(node->right, settings, lines, cur_depth + 1);
	}

	/*
num_layers is how many layers the binary tree has
ex: this would have num_layers of 3
      ___10___        
     /        \
   10         10            this looks bad 
  /  \       /  \           because itallics btw
10    10    10    10

string_len is the size of the biggest value we are printing (ex 10 has 2 string_len)
gap is the gap between the values on the lowest level of the tree
in this case it is 4

usually gap is calculated by string_len + 2
but i keep the option open here for fun :)

formula is

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                         ;
; 1 + 2^(depth - 3)string_length + (2^(depth - 3) - 1)gap ;
;                                                         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

note that depth subtracts 3
because formula only works 3+
any depth below below 3 will have no padding

        10
       /  \     this has 2 depth and therefore no padding.
     10    10
*/
	int getPadding(const PrintSettings& settings, int pad_depth)
	{
		//we subtract 3 because formula only starts working at
		//3+, anthything lower than 3 there is 0 padding

		/*   last and second-last layer won't have padding

EX:            ...   
                 \
                 1  -2nd last layer
               /  \
              1    1 - last layer
		                                     */
		int normalized_depth = pad_depth - 3;

		if(normalized_depth < 0)
			return 0;

		int coefficient = 1 << normalized_depth;

		int padding = 1 + (coefficient * settings.max_string_length) +
					  ((coefficient - 1) * settings.gap_size);

		return padding;
	}

	int GetNodeDistance(const PrintSettings& settings, const int& cur_depth)
	{
		//last depth
		if(cur_depth >= settings.num_layers - 1)
			return settings.gap_size;

		int pad_depth = settings.num_layers - cur_depth;

		int padding_above_layer = getPadding(settings, pad_depth + 1);

		/* _____STRLEN_____
          /                \ */

		int offset = 1 + padding_above_layer + settings.max_string_length + padding_above_layer + 1;
		return offset;
	}

	void GetNumLayers(TNode<T>* node, int& num_layers, int cur_depth = 1)
	{
		if(!node)
			return;

		if(cur_depth > num_layers)
			num_layers = cur_depth;

		GetNumLayers(node->left, num_layers, cur_depth + 1);
		GetNumLayers(node->right, num_layers, cur_depth + 1);
	}

	template <typename Lambda>
	void GetMaxStringLength(TNode<T>* node, int& max_string_length, Lambda func)
	{
		if(!node)
			return;

		std::string data = func(node->data);

		if(data.length() > max_string_length)
			max_string_length = data.length();

		GetMaxStringLength(node->left, max_string_length, func);
		GetMaxStringLength(node->right, max_string_length, func);
	}

	void SatiateTree(TNode<T>* parent, std::deque<T> values)
	{
		//no values to satiate with,
		//exit recursion
		if(values.empty())
			return;

		//only one value left, can't split anymore
		if(values.size() == 1)
		{
			TNode<T>* left = new TNode<T>(parent);
			parent->left = left;
			left->data = values.front();
			values.pop_front();
			return;
		}

		std::deque<T> s1, s2;

		splitDeque(values, s1, s2);

		TNode<T>* left = new TNode<T>(parent);
		parent->left = left;

		TNode<T>* right = new TNode<T>(parent);
		parent->right = right;

		//We know there are atleast 2 values so s1/s2 can't be 0
		left->data = s1.front();
		s1.pop_front();

		right->data = s2.front();
		s2.pop_front();

		//We could further check if s1/s2 is empty before running
		//SatiateTree but values.empty is checked anyway
		//so for simplicity i didn't check for it here

		SatiateTree(left, s1);
		SatiateTree(right, s2);
	}

	void splitDeque(std::deque<T>& original, std::deque<T>& split1, std::deque<T>& split2)
	{
		while(!original.empty())
		{
			if(split1.size() <= split2.size())
			{
				split1.push_back(original.front());
				original.pop_front();
			}
			else
			{
				split2.push_back(original.front());
				original.pop_front();
			}
		}
	}
};
