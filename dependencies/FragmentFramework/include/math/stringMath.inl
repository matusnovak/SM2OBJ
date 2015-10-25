/*** This file is part of FragmentFramework project ***/

///=============================================================================
template <> inline float                ffw::stringToVal<float>              (const std::string& Str){return std::stof(Str);}
template <> inline double               ffw::stringToVal<double>             (const std::string& Str){return std::stod(Str);}
template <> inline long double          ffw::stringToVal<long double>        (const std::string& Str){return std::stold(Str);}
template <> inline short                ffw::stringToVal<short>              (const std::string& Str){return static_cast<short>(std::stoi(Str));}
template <> inline int                  ffw::stringToVal<int>                (const std::string& Str){return std::stoi(Str);}
template <> inline long                 ffw::stringToVal<long>               (const std::string& Str){return std::stol(Str);}
template <> inline long long            ffw::stringToVal<long long>          (const std::string& Str){return std::stoll(Str);}
template <> inline unsigned short       ffw::stringToVal<unsigned short>     (const std::string& Str){return (unsigned short)std::stoul(Str);}
template <> inline unsigned int         ffw::stringToVal<unsigned int>       (const std::string& Str){return std::stoul(Str);}
template <> inline unsigned long        ffw::stringToVal<unsigned long>      (const std::string& Str){return std::stoul(Str);}
template <> inline unsigned long long   ffw::stringToVal<unsigned long long> (const std::string& Str){return std::stoull(Str);}

///=============================================================================
template <class T>
inline std::string ffw::valToString(const T& Value){
    return std::to_string(Value);
}

///=============================================================================
template <class T>
inline std::string ffw::valToString(T Value, unsigned int Dec){
    std::ostringstream ostr;
    ostr.precision(Dec);
    ostr << std::fixed << Value;
    return ostr.str();
}

///=============================================================================
template<typename T>
inline T ffw::hexToVal(const std::string& Str) {
    try {
        return std::stoul(Str, nullptr, 16);
    } catch (std::invalid_argument e){
        return 0;
    } catch (std::out_of_range e){
        return 0;
    }
    return 0;
}

///=============================================================================
template<typename T>
inline std::string ffw::valToHex(const T& Value) {
    std::stringstream ss;
    ss << std::hex << Value;
    std::string h = ss.str();
    if(h.size() < sizeof(T)*2){
        return std::string(sizeof(T)*2 - h.size(), '0') + h;
    }
    return h;
}

///=============================================================================
template<class T>
inline std::vector<T> ffw::getTokens(const T& Line, char Delim){
    std::vector<T> vec;
    T temp;
    for(unsigned int i = 0; i < Line.size(); i++){
        if(Line[i] != Delim)temp += Line[i];
        else if(temp.size() > 0){
            vec.push_back(temp);
            temp = "";
        }
        if(i == Line.size()-1 && Line[i] != Delim)vec.push_back(temp);
    }
    return vec;
}

///=============================================================================
template<class T>
inline unsigned int ffw::getTokensNum(const T& Line, char Delim){
    int num = 0;
	int temp = 0;
    for(unsigned int i = 0; i < Line.size(); i++){
        if(Line[i] != Delim)temp++;
		else if(temp > 0){
            num++;
            temp = 0;
        }
        if(i == Line.size()-1 && Line[i] != Delim)num++;
    }
    return num;
}
