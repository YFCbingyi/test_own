#include <iostream>

//This encrypt function increment all letters in string by 1.
std::string encryptDataByLetterInc1(std::string data) {
    for (int i = 0; i < data.size(); i++)
        if ((data[i] >= 'a' && data[i] <= 'z')
                || (data[i] >= 'A' && data[i] <= 'Z'))
            data[i]++;
    return data;
}
//This encrypt function increment all letters in string by 2.
std::string encryptDataByLetterInc2(std::string data) {
    for (int i = 0; i < data.size(); i++)
        if ((data[i] >= 'a' && data[i] <= 'z')
                || (data[i] >= 'A' && data[i] <= 'Z'))
            data[i] = data[i] + 2;
    return data;
}
//This encrypt function increment all letters in string by 1.
std::string encryptDataByLetterDec(std::string data) {
    for (int i = 0; i < data.size(); i++)
        if ((data[i] >= 'a' && data[i] <= 'z')
                || (data[i] >= 'A' && data[i] <= 'Z'))
            data[i] = data[i] - 1;
    return data;
}

class Encryptor {
    bool m_isIncremental;
    int m_count;
public:
    Encryptor() {
        m_isIncremental = 0;
        m_count = 1;
    }
    Encryptor(bool isInc, int count) {
        m_isIncremental = isInc;
        m_count = count;
    }
    std::string operator()(std::string data) {
        for (int i = 0; i < data.size(); i++)
            if ((data[i] >= 'a' && data[i] <= 'z')
                    || (data[i] >= 'A' && data[i] <= 'Z')) {
                if (m_isIncremental)
                    data[i] = data[i] + m_count;
                else
                    data[i] = data[i] - m_count;
            }
        return data;
    }
 
};

std::string buildCompleteMessage(std::string rawData,
        std::string (*encrypterFunPtr)(std::string)) {
    // Add some header and footer to data to make it complete message
    rawData = "[HEADER]" + rawData + "[FooTER]";
 
    // Call the callBack provided i.e. function pointer to encrypt the
    rawData = encrypterFunPtr(rawData);
 
    return rawData;
}
std::string buildCompleteMessage2(std::string rawData,
        Encryptor encyptorFuncObj) {
    // Add some header and footer to data to make it complete message
    rawData = "[HEADER]" + rawData + "[FooTER]";
 
    // Call the callBack provided i.e. function pointer to encrypt the
    rawData = encyptorFuncObj(rawData);
 
    return rawData;
}


int main() {
    std::string msg = buildCompleteMessage("SampleString",
            &encryptDataByLetterInc1);
    std::cout << msg << std::endl;
 
    msg = buildCompleteMessage("SampleString", &encryptDataByLetterInc2);
    std::cout << msg << std::endl;
 
    msg = buildCompleteMessage("SampleString", &encryptDataByLetterDec);
    std::cout << msg << std::endl;
 
 
 	// functor
 	msg = buildCompleteMessage2("SampleString", Encryptor(true, 1));
    std::cout << msg << std::endl;
 
    msg = buildCompleteMessage2("SampleString", Encryptor(true, 2));
    std::cout << msg << std::endl;
 
    msg = buildCompleteMessage2("SampleString", Encryptor(false, 1));
    std::cout << msg << std::endl;
 
    return 0;
}