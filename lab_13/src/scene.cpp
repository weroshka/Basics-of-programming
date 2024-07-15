#include <scene.hpp>
#include <fstream>


namespace mt
{
	Scene::Scene(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), "3D Engine");
		m_texture = std::make_unique<sf::Texture>();
		m_texture->create(m_width, m_height);
		m_sprite = std::make_unique<sf::Sprite>(*m_texture);

		Intrinsic intrinsic = { 960.0, 540.0, 960.0, 540.0 };
		Point position = { 467386.0, -69.0, 6063536.860 };
		Angles angles = { 0.0,0.0,0.0 };
		m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);

		m_points = new Point[300000];
		m_pixels = new Pixel[300000];

		std::ifstream in("points.txt");

		if (!in.is_open())
			std::cerr << "File not found" << std::endl;

		while (!in.eof())
		{
			double x, y, z;
			int r, g, b;

			in >> x >> y >> z >> r >> g >> b;

			m_points[m_size].x = x;
			m_points[m_size].y = y;
			m_points[m_size].z = z;
			m_pixels[m_size].r = r;
			m_pixels[m_size].g = g;
			m_pixels[m_size].b = b;

			m_size++;
		}

		/*
		double r = 1;
		for(double fi = 0; fi < 6.28; fi += 0.01)
			for (double teta = 0; teta < 1.57; teta += 0.01)
			{
				m_points[m_size].x = r * sin(teta) * cos(fi);
				m_points[m_size].y = r * sin(teta) * sin(fi) + 5;
				m_points[m_size].z = r * cos(teta);
				m_size++;
			}*/
	}
	Scene::~Scene()
	{
		if (m_points != nullptr)
			delete[] m_points;
	}

	void Scene::LifeCycle()
	{
		while (m_window->isOpen()) 
		{
			sf::Event event;
			while (m_window->pollEvent(event))
				if (event.type == sf::Event::Closed)
					m_window->close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_camera->dZ(0.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_camera->dZ(-0.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_camera->dX(-0.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_camera->dX(0.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				m_camera->dPitch(-0.02);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_camera->dPitch(0.02);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_camera->dRoll(-0.02);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				m_camera->dRoll(0.02);
			}

			//  
			for (int i = 0; i < m_size; i++)
				m_camera->ProjectPoint(m_points[i], { m_pixels[i].r, m_pixels[i].g, m_pixels[i].b, 255 });

			m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);

			m_window->display();

		}
	}
}
