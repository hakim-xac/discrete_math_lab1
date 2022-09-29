#pragma once

#include <iostream>
#include <sstream>


namespace KHAS {
    class CommonInterface
    {

    private:    // section for fields

        //* stream buffer */
        std::ostream& cout_;

        //* temprory buffer */
        std::stringstream out_buffer_;

        //* output table width */
        const std::size_t table_width_;
        const std::size_t min_table_width_{ 100 };

    private:    // section for member functions

        //* reset to output */
        void flush();

        //* clear out_buffer_ */
        void clearOutBuffer();

        //* creates a string of length table_width_ and */
        std::string delimiter(char del) const;

    private:    // section for templates 

        //* forwards a string "str" to a temporary buffer "out_buffer_" */
        template <typename TString>
        void push(TString&& str);

        //* generates a string of length table_width_ from the given arguments */
        template <typename ... TString>
        std::string stringGeneration(char aggregate = ' ', TString&& ... str);

    protected:

        //* prints the header to a stream */
        void showHeader();


    public: // public section

        CommonInterface() = delete;
        virtual ~CommonInterface() {};

        //* params */
        // first:   size_t          table_width_    | not default
        // second:  std::ostream&   out_            | default: std::cout
        CommonInterface(std::size_t table_width, std::ostream& out = std::cout);

        //* main program loop */
        virtual void loop() = 0;
    };
}

#include "CommonInterface.hpp"
