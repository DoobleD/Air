#include "OpenNIBox.hpp"
#include "error.hpp"


using namespace air;


void			OpenNIBox::initialize(void)
{
  XnStatus		rs;

  // Initilizing context
  rs = m_context.Init();
  CHECK_RS(rs, "Context::Init");


  // Set main generators
  rs = m_gestureGenerator.Create(m_context);
  CHECK_RS(rs, "GestureGenerator::Create");
  rs = m_handsGenerator.Create(m_context);
  CHECK_RS(rs, "HandsGenerator::Create");
  rs = m_depthGenerator.Create(m_context);
  CHECK_RS(rs, "DepthGenerator::Create");

  // This my own OpenNI production node, detecting finger tips
  rs = m_fingersGenerator.Create(m_context);
  CHECK_RS(rs, "FingersGenerator::Create");


  // Some configuration
  m_handsGenerator.SetSmoothing((XnFloat) 0.1);
  xn::MirrorCapability	mirror(m_depthGenerator);
  mirror.SetMirror(true);


  // Start generating
  rs = m_context.StartGeneratingAll();
  CHECK_RS(rs, "Context::StartGenerating");
}
    
void			OpenNIBox::waitAndUpdate(void)
{
  XnStatus		rs;
  
  rs = m_context.WaitAndUpdateAll();
  CHECK_RS(rs, "Context::WaitAndUpdateAll");
}

void			OpenNIBox::stop(void)
{
  // Clean up
  m_context.Release();
  //m_context.Shutdown();
}

xn::Context &		OpenNIBox::getContext(void)
{
  return m_context;
}

xn::DepthGenerator &	OpenNIBox::getDepthGenerator(void)
{
  return m_depthGenerator;
}

xn::FingersGenerator &	OpenNIBox::getFingersGenerator(void)
{
  return m_fingersGenerator;
}
