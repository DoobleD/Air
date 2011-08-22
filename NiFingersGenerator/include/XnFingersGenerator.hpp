#ifndef _XN_FINGERS_GENERATOR_HPP_
#define _XN_FINGERS_GENERATOR_HPP_


#include <XnCppWrapper.h>

#include "XnFingersExtractor.hpp"


namespace xn
{

  /**
   * OpenNI compliant production node for finger detection. Inherit from HandsGenerator
   * since the algorithm is based on the hand detection and position.
   *
   * @author Pierre Alletru
   */
  class					FingersGenerator : public HandsGenerator
  {

  public:

    // Callbacks typedef.
    typedef void (XN_CALLBACK_TYPE * FingersCreate)(FingersGenerator & generator, 
						    XnUserID id,
						    xn::FingersData * data,
						    XnFloat time, 
						    void * cookie);
    typedef void (XN_CALLBACK_TYPE * FingersUpdate)(FingersGenerator & generator, 
						    XnUserID id, 
						    xn::FingersData * data,
						    XnFloat time, 
						    void * cookie);
    typedef void (XN_CALLBACK_TYPE * FingersDestroy)(FingersGenerator & generator, 
						     XnUserID id, 
						     XnFloat time, 
						     void * cookie);


    /**
     * Initialize the generator. Must be called before any other method.
     *
     * @param context			OpenNI context object.
     * @param query			Optional. OpenNI query object.
     * @param errors			Optional. OpenNI enumeration errors object.
     *
     * @return XN_STATUS_OK if successful.
     */
    virtual XnStatus			Create(Context & context, 
					       Query * query = NULL, 
					       EnumerationErrors * errors = NULL);

    /**
     * Register user callbacks relative to fingers events.
     * 
     * @param CreateCB			The callback used for first fingers detection.
     * @param UpdateCB			The callback used every frame 
     *					to update fingers detection.
     * @param DestroyCB			The callback used when fingers/hand are lost.
     * @param userCookie		A pointer to some data the user want to
     *					transmit when callbacks are actually called.
     *
     * @return XN_STATUS_OK if successful.
     */
    virtual XnStatus			RegisterFingersCallbacks(FingersCreate CreateCB, 
								 FingersUpdate UpdateCB, 
								 FingersDestroy DestroyCB,
								 void * userCookie);

    /**
     * Unregister the fingers callbacks.
     */
    virtual void			UnregisterFingersCallbacks(void);
    
    /**
     * Set the persistence of fingers (see XnFingersExtractor.hpp).
     *
     * @param nbOfFrames		The number of frame a finger stay detected
     *					after it disappeard.
     */
    virtual void			SetPersitence(int nbOfFrames);

    /**
     * Enable or disable smoothing.
     *
     * @param b				A booelan. True enables smoothing, 
     *					false disables it.
     */
    virtual void			SetSmoothing(bool b);

  private:

    /**
     * Contains some data transmitted to hand callbacks.
     */
    struct				FingersCookie
    {
      FingersCreate			createHandler;
      FingersUpdate			updateHandler;
      FingersDestroy			destroyHandler;
      void *				userCookie;
      Context				context;
    };

    // The data to transmitt to hand callbacks.
    FingersCookie *			m_fingersCookie;
    // A handle to hand callbacks.
    XnCallbackHandle			m_handsCBHandle;
    // OpenNI context.
    Context				m_context;
    
    // Fingers extractor. Contains the actual algorithm used to detect finger tips.
    static FingersExtractor		m_extractor;

    
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
