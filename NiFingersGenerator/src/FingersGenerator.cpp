#include "XnFingersGenerator.hpp"


using namespace xn;


FingersExtractor	FingersGenerator::m_extractor;


XnStatus		FingersGenerator::Create(Context & context, 
						 Query * query, 
						 EnumerationErrors * errors)
{
  m_context = context;
  return HandsGenerator::Create(context, query, errors);
}

void XN_CALLBACK_TYPE	FingersGenerator::HandCreate(xn::HandsGenerator & handGenerator,
						     XnUserID id, 
						     const XnPoint3D * position,
						     XnFloat time, 
						     void * cookie)
{
  FingersCookie *	fingersCookie = (FingersCookie *) cookie;
  FingersData *		outData;
  
  outData = m_extractor.Extract(fingersCookie->context, position);

  fingersCookie->createHandler((FingersGenerator &) handGenerator, 
			       id, outData, time, cookie);

  delete outData;
}

void XN_CALLBACK_TYPE	FingersGenerator::HandUpdate(xn::HandsGenerator & handGenerator,
						     XnUserID id, 
						     const XnPoint3D * position,
						     XnFloat time, 
						     void * cookie)
{
  FingersCookie *		fingersCookie = (FingersCookie *) cookie;
  FingersData *			outData;

  outData = m_extractor.Extract(fingersCookie->context, position);

  fingersCookie->updateHandler((FingersGenerator &) handGenerator, 
			       id, outData, time, cookie);

  delete outData;
}

void XN_CALLBACK_TYPE	FingersGenerator::HandDestroy(xn::HandsGenerator& handGenerator,
						      XnUserID id, 
						      XnFloat time,
						      void * cookie)
{
  FingersCookie *	fingersCookie = (FingersCookie *) cookie;
  
  m_extractor.Reset();

  fingersCookie->destroyHandler((FingersGenerator &) handGenerator, 
				id, time, cookie);
}

XnStatus	FingersGenerator::RegisterFingersCallbacks(FingersCreate createCB,
							   FingersUpdate updateCB,
							   FingersDestroy destroyCB,
							   void * userCookie)
{
  XnStatus	status;

  m_fingersCookie = new FingersCookie();
  m_fingersCookie->createHandler = createCB;
  m_fingersCookie->updateHandler = updateCB;
  m_fingersCookie->destroyHandler = destroyCB;
  m_fingersCookie->userCookie = userCookie;
  m_fingersCookie->context = m_context;

  status = HandsGenerator::RegisterHandCallbacks(FingersGenerator::HandCreate, 
						 FingersGenerator::HandUpdate, 
						 FingersGenerator::HandDestroy, 
						 m_fingersCookie, m_handsCBHandle);

  return status;
}

void		FingersGenerator::UnregisterFingersCallbacks(void)
{
  HandsGenerator::UnregisterHandCallbacks(m_handsCBHandle);

  delete m_fingersCookie;
}

void		FingersGenerator::SetPersitence(int nbOfFrames)
{
  m_extractor.SetPersistence(nbOfFrames);
}
