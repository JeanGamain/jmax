#ifndef BIND_H_
# define BIND_H_

# include <map>
# include <list>
# include <utility>

// Input event binding class with tick sync

namespace jmax
{
	class bind
	{
	public:

		typedef struct s_bindValue {
			s_bindValue()
				: value(0), status(0), active(0), funct(NULL) {};
			s_bindValue(void *h)
				: value(0), status(0), active(0), funct(h) {};
			int			value;
			int			status;
			int			active;
			void		*funct;
		}				bindValue;

		typedef void(*bindFunct)(unsigned int tick, bind *binding, bindValue *my);

	public:
		bind(std::map<int, bindValue> binding);

	public:
		std::map<int, bindValue>	binding;

	public:
		void	runActive();
		void	addBind(int newkey);

		bindValue  operator[](int key)
		{
			std::map<int, bindValue>::iterator val = binding.find(key);
			if (val == binding.end())
				return bindValue();
			return val->second;
		};
	};
}

#endif /* !BIND_H_ */
