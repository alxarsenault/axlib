/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of OpenAX.
 *
 * OpenAX is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * license or use a commercial OpenAX License.
 *
 * OpenAX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenAX. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses OpenAX, commercial
 * licenses are available, email ax.frameworks@gmail.com for more information.
 */

#ifndef __AX_LABEL__
#define __AX_LABEL__

/// @defgroup Widgets
/// @{

/// @defgroup Label
/// @{

#include "axlib.hpp"

namespace ax {
class Label : public ax::Window::Backbone {
public:
	class Info : public ax::widget::Info {
	public:
		Info();

		Info(const std::vector<std::pair<std::string, std::string>>& attributes);

		virtual std::vector<std::string> GetParamNameList() const;
		
		virtual std::string GetAttributeValue(const std::string& name);
		
		virtual void SetAttribute(const std::pair<std::string, std::string>& attribute);
		
		virtual std::vector<widget::ParamInfo> GetParametersInfo() const;

		ax::Color normal;
		ax::Color contour;
		ax::Color font_color;
		int font_size;
		std::string font_name;
		ax::util::Alignement alignement;
	};

	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		virtual ax::Xml::Node Save(ax::Xml& xml, ax::Xml::Node& node);
		virtual std::vector<std::pair<std::string, std::string>> GetBuilderAttributes();
		std::vector<ax::widget::ParamInfo> GetBuilderAttributesInfo() const;

		std::string GetBuilderName() const
		{
			return "Label";
		}

		virtual void SetBuilderAttributes(const std::vector<std::pair<std::string, std::string>>& attributes);
		
		
		virtual void SetInfo(const std::vector<std::pair<std::string, std::string>>& attributes);
		virtual void ReloadInfo();
	};

	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);
	};

	Label(const ax::Rect& rect, const Label::Info& info, const std::string& label);

	ax::Window::Backbone* GetCopy();

	void SetLabel(const std::string& label);

	std::string GetLabel() const
	{
		return _label;
	}

private:
	std::string _label;
	std::unique_ptr<ax::Font> _font;

	// Events.
	void OnPaint(ax::GC gc);
};
}

/// @}
/// @}
#endif // __AX_LABEL__.
