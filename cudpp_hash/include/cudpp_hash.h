#include "cudpp.h"

/* To use CUDPP_HASH as a static library, #define CUDPP_HASH_STATIC_LIB before 
 * including cudpp.h
 */
#ifndef CUDPP_HASH_DLL
    #ifdef _WIN32
        #ifdef CUDPP_HASH_STATIC_LIB
            #define CUDPP_HASH_DLL
        #else
        #ifdef BUILD_DLL
            #define CUDPP_HASH_DLL __declspec(dllexport)
        #else
            #define CUDPP_HASH_DLL __declspec(dllimport)
        #endif
        #endif
    #else
        #define CUDPP_HASH_DLL
    #endif
#endif

enum CUDPPHashTableType
{
    CUDPP_BASIC_HASH_TABLE,
    CUDPP_COMPACTING_HASH_TABLE,
    CUDPP_MULTIVALUE_HASH_TABLE,
    CUDPP_INVALID_HASH_TABLE,
};

struct CUDPPHashTableConfig
{
    CUDPPHashTableType type;
    unsigned int kInputSize;
    float space_usage;
};

template<class T>
class CUDPPHashTableInternal
{
public:
    CUDPPHashTableInternal(const CUDPPHashTableConfig * c, T * t) : 
        config(*c), hash_table(t) {}
    CUDPPHashTableConfig config;
    T * hash_table;
    // template<typename T> T getHashTablePtr()
    // {
        // return reinterpret_cast<T>(hash_table);
        // }
    //! @internal Convert this pointer to an opaque handle
    CUDPPHandle getHandle()
    {
        return reinterpret_cast<CUDPPHandle>(this);
    }
    ~CUDPPHashTableInternal() 
    {
        delete hash_table;
    }
};

CUDPPResult
cudppHashTable(CUDPPHandle *plan, const CUDPPHashTableConfig *config);

CUDPPResult
cudppHashInsert(CUDPPHandle plan, const void* d_keys, 
                const void* d_vals, unsigned int num);

CUDPPResult
cudppHashRetrieve(CUDPPHandle plan, const void* d_keys, void* d_vals, 
                  size_t num);

CUDPPResult
cudppDestroyHashTable(CUDPPHandle plan);

// Leave this at the end of the file
// Local Variables:
// mode:c++
// c-file-style: "NVIDIA"
// End:

