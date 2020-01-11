#include "book.hh"
#include <iostream>

Book::Book(const std::string& title, std::vector<Person*> authors,
           std::string description, std::set<std::string> genres) :
    title_(title),
    authors_(authors),
    description_(description),
    genres_(genres)
{

}

Book::~Book()
{

}

std::string Book::get_title() const
{
    return title_;
}

std::vector<Person *> Book::get_authors() const
{
    return authors_;
}

std::set<std::string> Book::get_genres() const
{
    return genres_;
}

void Book::print_info() const
{
    std::cout << "Title: " << title_ << std::endl;
    std::cout << "Authors: ";
    for ( auto author : authors_ ){
        std::cout << author->get_name();
        if ( author != authors_.back() ){
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Description: " << description_ << std::endl;
    std::cout << "Genres: ";
    auto genre = genres_.begin();
    std::cout << *genre;
    ++genre;
    while(genre != genres_.end())
    {
        std::cout << ", ";
        std::cout << *genre;
        ++genre;
    }
    std::cout << std::endl;
}

bool Book::has_keyword(const std::string& keyword) const
{
    if ( title_.find(keyword) != std::string::npos
         || description_.find(keyword) != std::string::npos ){
        return true;
    }

    for ( Person* author : authors_ ){
        if ( author->get_name().find(keyword) != std::string::npos ){
            return true;
        }
    }

    for ( auto genre : genres_ ){
        if ( genre.find(keyword) != std::string::npos ){
            return true;
        }
    }

    return false;
}

bool Book::has_author(Person *author) const
{
    for ( Person* person : authors_ ){
        if ( person == author){
            return true;
        }
    }
    return false;
}

bool Book::has_genre(const std::string &genre) const
{
    return ( genres_.find(genre) != genres_.end());
}

