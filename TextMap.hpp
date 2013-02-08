#ifndef __TEXTMAP__
#define __TEXTMAP__

#include "all.hpp"

class TextMap
{
private:
  int		xMax_;
  int		yMax_;
  int		size_;
  gdl::Image	texture_;
  std::string	content_;
  bool		pop_;

public:
  TextMap();
  TextMap(std::string const & file);
  TextMap(std::string const & file, int, int);
  ~TextMap();

  void		setContent(std::string const &);
  void		setPopup(bool const &);
  void		setMap(std::string const & file);
  void		setSize(int size);
  void		putChar(char c);
  void		putStr(std::string const);
  void		popup(void);
};

#endif
