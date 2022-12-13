/***************************************************************************
 * ROM Properties Page shell extension. (KDE)                              *
 * AchievementsTab.hpp: Achievements tab for rp-config.                    *
 *                                                                         *
 * Copyright (c) 2016-2022 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_KDE_CONFIG_ACHIEVEMENTSTAB_HPP__
#define __ROMPROPERTIES_KDE_CONFIG_ACHIEVEMENTSTAB_HPP__

#include "ITab.hpp"

class AchievementsTabPrivate;
class AchievementsTab final : public ITab
{
	Q_OBJECT

	public:
		explicit AchievementsTab(QWidget *parent = nullptr);
		~AchievementsTab() final;

	private:
		typedef ITab super;
		AchievementsTabPrivate *const d_ptr;
		Q_DECLARE_PRIVATE(AchievementsTab);
		Q_DISABLE_COPY(AchievementsTab)

	public:
		/**
		 * Does this tab have defaults available?
		 * If so, the "Defaults" button will be enabled.
		 * Otherwise, it will be disabled.
		 *
		 * AboutTab sets this to false.
		 *
		 * @return True to enable; false to disable.
		 */
		bool hasDefaults(void) const final { return false; }

	protected:
		// State change event. (Used for switching the UI language at runtime.)
		void changeEvent(QEvent *event) final;

	public slots:
		/**
		 * Reset the configuration.
		 */
		void reset(void) final;

		/**
		 * Save the configuration.
		 * @param pSettings QSettings object.
		 */
		void save(QSettings *pSettings) final
		{
			// Nothing to do here.
			Q_UNUSED(pSettings)
		}
};

#endif /* __ROMPROPERTIES_KDE_CONFIG_ACHIEVEMENTSTAB_HPP__ */
