#ifndef _XN_FINGERS_GENERATOR_HPP_
#define _XN_FINGERS_GENERATOR_HPP_

#include <XnCppWrapper.h>

#include "XnFingersExtractor.hpp"


namespace xn
{

  class					FingersGenerator : public xn::HandsGenerator
  {
  public:
    
    typedef void (XN_CALLBACK_TYPE * FingersCreate)(FingersGenerator & generator, 
						    XnUserID id,
						    const xn::FingersData * data,
						    XnFloat time, 
						    void * cookie);
    typedef void (XN_CALLBACK_TYPE * FingersUpdate)(FingersGenerator & generator, 
						    XnUserID id, 
						    const xn::FingersData * data,
						    XnFloat time, 
						    void * cookie);
    typedef void (XN_CALLBACK_TYPE * FingersDestroy)(FingersGenerator & generator, 
						     XnUserID id, 
						     XnFloat time, 
						     void * cookie);


    virtual XnStatus			Create(Context & context, 
					       Query * query = NULL, 
					       EnumerationErrors * errors = NULL);

    virtual XnStatus			RegisterFingersCallbacks(FingersCreate CreateCB, 
    							 FingersUpdate UpdateCB, 
    							 FingersDestroy DestroyCB,
    							 void * userCookie);
    virtual void			UnregisterFingersCallbacks(void);

  private:

    struct				FingersCookie
    {
      FingersCreate			createHandler;
      FingersUpdate			updateHandler;
      FingersDestroy			destroyHandler;
      void *				userCookie;
      Context				context;
    };

    FingersCookie *			m_fingersCookie;
    XnCallbackHandle			m_handsCBHandle;
    Context				m_context;

    // Forbid access to certain hand methods
    virtual XnStatus			SetSmoothing(XnFloat) {}

    // Hand callbacks 
    static void XN_CALLBACK_TYPE	HandCreate(xn::HandsGenerator & handGenerator,
    						   XnUserID id, 
    						   const XnPoint3D * position,
    						   XnFloat time, 
    						   void * cookie);
    static void XN_CALLBACK_TYPE	HandUpdate(xn::HandsGenerator & handGenerator,
    						   XnUserID id, 
    						   const XnPoint3D * position,
    						   XnFloat time, 
    						   void * cookie);
    static void XN_CALLBACK_TYPE	HandDestroy(xn::HandsGenerator & handGenerator,
    						    XnUserID id, 
    						    XnFloat time,
    						    void* cookie);
  };

}

#endif //_XN_FINGERS_GENERATOR_HPP_
