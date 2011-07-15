#include "OpenNIBox.hpp"
#include "NITEBox.hpp"
#include "error.hpp"

using namespace air;

extern NITEBox		g_NITE;


void			OpenNIBox::initialize(void)
{
  XnStatus		rs;

  rs = m_context.Init();
  CHECK_RS(rs, "Context::Init");
      
  rs = m_gestureGenerator.Create(m_context);
  CHECK_RS(rs, "GestureGenerator::Create");
  rs = m_handsGenerator.Create(m_context);
  CHECK_RS(rs, "HandsGenerator::Create");
  rs = m_depthGenerator.Create(m_context);
  CHECK_RS(rs, "DepthGenerator::Create");
      
  m_handsGenerator.SetSmoothing((XnFloat) 0.1);
      
  xn::MirrorCapability	mirror(m_depthGenerator);
  mirror.SetMirror(true);
}
    
void			OpenNIBox::run()
{
  XnStatus		rs;
  XnVSessionManager &	session = g_NITE.getSession();

  // Start generating
  rs = m_context.StartGeneratingAll();
  CHECK_RS(rs, "Context::StartGenerating");
      
  while (TRUE) 
    { 
      // Update to next frame 
      rs = m_context.WaitAndUpdateAll();
      CHECK_RS(rs, "Context::WaitAndUpdateAll");
	  
      session.Update(&m_context);
    } 
}

void			OpenNIBox::stop(void)
{
  // Clean up
  m_context.Shutdown();
}

xn::Context &		OpenNIBox::getContext(void)
{
  return m_context;
}

xn::DepthGenerator &	OpenNIBox::getDepthGenerator(void)
{
  return m_depthGenerator;
}

