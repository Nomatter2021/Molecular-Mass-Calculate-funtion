#include "String.cpp"
#include <iostream>
#include <cstring>
#include <map>
#include <fstream>
#include <iomanip>

void fagment(std::string &fg, std::string &mg, std::string &lg, std::string nm);
void brk(std::string nm, std::map<std::string, int> &store, int p);
void str(std::string nm, int p, int m, std::map<std::string, int> &store);
void load_periodic(std::map<std::string, float> &periodic);
void check(int i, std::string nm, std::map<std::string, int> &store);
void loadm(int &n, int &m, int i, std::string nm);
float cal_chem(std::map<std::string, float> periodic, std::map<std::string, int> store);
float Mass(std::string nm);


float Mass(std::string nm)
{
	std::map <std::string, int> store;
	std::map <std::string, float> per;
	std::string fg, mg, lg;
	int p{1}, key, l{static_cast<int>(nm.length())};
	for(int i{0}; i < l; i++)
	{
		if(nm[i] == '.')
		{
			check(i, nm, store);
			nm = nm.substr(0, i);
			break;
		};	
	};
	fagment(fg, mg, lg, nm);
	if(isdigit(lg[0]) == 1)
	{
		int i{1};
		while(true)
		{
			if(isdigit(lg[i]) == 1)
			{
				i++;
			}
			else
			{
				p *= std::stoi(lg.substr(0, i));
				break;
			}
		};
		brk(fg, store, 1);
		brk(mg, store, p);
		brk(lg, store, 1);
	}
	else
	{
		brk(fg, store, 1);
		brk(mg, store, 1);
	};

	load_periodic(per);
	return cal_chem(per, store);
};


void fagment(std::string &fg, std::string &mg, std::string &lg, std::string nm)
{
	int i{0}, l{0}, f{0};
	int lc{static_cast <int> (nm.length())};
	while(i < lc)
	{
		if(f == 0)
		{
			if(nm[i] == '(')
			{
				f = i;
				i += 1;
			}
			else
			{
				i += 1;
			};
		}
		else
		{
			if(nm[i] ==')')
			{
				l = i;
				i += 1;
			}
			else
			{
				i += 1;
			};
		};
	};
	if(f == 0)
	{
		fg = nm;
	}
	else
	{
		fg = nm.substr(0, f);
		mg = nm.substr(f + 1, l - f - 1);
		lg = nm.substr(l + 1, lc - 1);
	};
};


void brk(std::string nm, std::map<std::string, int> &store, int p)
{
	std::string o;
	int n{0};
	int i{static_cast <int> (nm.length())};
	if(isdigit(nm[n]) == 1)
	{
		for(int i{0}; i < static_cast<int>(nm.length()); i++)
		{
			if(isdigit(nm[i] == 1))
			{
				i++;
			}
			else
			{
				n += i;
			};
		};
	};
	while(n <= i - 1)
	{
		int m{1};
		if(isupper(nm[n]) == 1)
		{
			if(isdigit(nm[n + 1]) == 1)
			{
				//Tại đây nguyên tố có một ký tự và có kèm số lượng
				o = nm.substr(n, 1);
				loadm(n, m, 1, nm);
				str(o, p, m, store);
			}
			else
			{
				if(isupper(nm[n + 1]) == 1)
				{
					//Tại đây nguyên tố có một ký tự và không kèm theo số lượng
					o = nm.substr(n, 1);
					str(o, p, m, store);
					n += 1;
				}
				else
				{
					if(isdigit(nm[n + 2]) == 1)
					{
						//Tại đây nguyên tố có hai ký tự và có kèm số lượng
						o = nm.substr(n, 2);
						loadm(n, m, 2, nm);
						str(o, p, m, store);
					}
					else
					{
						//Tại đây nguyên tố có hai ký tự và không kèm số lượng
						o = nm.substr(n, 2);
						str(o, p, m, store);
						n += 2;
					};
				};
			};
		}
		else
		{
			//Tại đây nguyên tố có một ký tự và không kèm số lượng
			o = nm.substr(n, 1);
			str(o, p, m, store);
			n += 1;
		};
	};			
};


void str(std::string nm, int p, int m, std::map<std::string, int> &store)
{
	if(store.find(nm) != store.end())
	{
		store.at(nm) += 1*p*m;
	}
	else
	{
		store.insert(make_pair(nm, 1*p*m));
	};
};


void load_periodic(std::map<std::string, float> &periodic)
{
	std::fstream outfile;
	Separ S;
	std::string Perio_name = "PeriodicTableElements.txt";
	std::string a, b;
	float value;
	outfile.open(Perio_name, std::ios::in);
	while (getline(outfile, a))
	{
		b = S.split_f(a, " ");
		value = std::stof(S.split_l(a, " "));
		periodic.insert(make_pair(b, value));
	};
	outfile.close();
};


float cal_chem(std::map<std::string, float> periodic, std::map<std::string, int> store)
{
	float r{0};
	for(std::pair<std::string, float> it : store)
	{
		r += periodic.at(it.first)*it.second;
	};
	return r;
};


void loadm(int &n, int &m, int i, std::string nm)
{
	int l{static_cast<int>(nm.length())};
	n += i;
	while(n < l)
	{
		if(isdigit(nm[n + i]) == 1)
		{
			i++;
		}
		else
		{
			m *= std::stoi(nm.substr(n, i));
			n += i;
			break;
		};
	};
};

void check(int i, std::string nm, std::map<std::string, int> &store)
{
	int j{i+1};
	while(true)
	{
		if(isdigit(nm[j] == 1))
		{
			j++;
		}
		else
		{
			store.insert(std::make_pair("H", 2*std::stoi(nm.substr(i + 1, j - i + 1))));
			store.insert(std::make_pair("O", std::stoi(nm.substr(i + 1, j - i + 1))));
			break;
		};
	};
};