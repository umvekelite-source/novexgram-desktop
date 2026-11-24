/*
This file is part of NovexGram Desktop.
Native Sovereign Suite & Creator GodMode Controls.
*/
#include "boxes/novexgram_godmode_box.h"

#include "ui/layers/generic_box.h"
#include "ui/text/text_utilities.h"
#include "ui/toast/toast.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/checkbox.h"
#include "ui/widgets/fields/special_fields.h"
#include "ui/widgets/labels.h"
#include "window/window_session_controller.h"
#include "main/main_session.h"
#include "data/data_user.h"
#include "config.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"

namespace NovexGram {

void ShowGodModeBox(not_null<Window::SessionController*> controller) {
	controller->uiShow()->show(Box([=](not_null<Ui::GenericBox*> box) {
		box->setTitle(rpl::single(u"⚡ NovexGram Sovereign & GodMode Suite"_q));

		// --- Header Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"👑 <b>Консоль Верховного Создателя (ID #1)</b><br/>"
			"Управление суверенным клиентом, значками верификации и номерами +888."_q,
			st::boxLabel));

		box->addSkip(10);

		// --- Badge Selector Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>Выбор значка профиля и статуса верификации:</b>"_q,
			st::boxLabel));

		const auto currentBadge = std::make_shared<QString>(u"👑 Корона Создателя"_q);

		const auto badgeLabel = box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			rpl::single(u"Текущий значок: 👑 Корона Создателя"_q),
			st::boxLabel));

		// Row of Badge Buttons
		const auto badges = std::vector<std::pair<QString, QString>>{
			{ u"👑 Корона"_q, u"👑 Корона Создателя (ID #1)"_q },
			{ u"✔️ Галочка"_q, u"✔️ Официальная Верификация"_q },
			{ u"⭐ Premium"_q, u"⭐ Telegram Premium Звезда"_q },
			{ u"💎 Алмаз"_q, u"💎 Основатель Экосистемы"_q },
			{ u"🔥 Огонь"_q, u"🔥 Огненный Статус"_q },
			{ u"🛡️ Щит"_q, u"🛡️ Суверенная Защита"_q },
		};

		for (const auto &[shortName, fullName] : badges) {
			box->addRow(object_ptr<Ui::RoundButton>(
				box,
				rpl::single(shortName + u" — " + fullName),
				st::defaultBoxButton
			))->setClickedCallback([=] {
				*currentBadge = fullName;
				badgeLabel->setText(u"Текущий значок: "_q + fullName);
				controller->uiShow()->showToast(u"Значок изменен на: "_q + fullName);
			});
			box->addSkip(3);
		}

		box->addSkip(12);

		// --- Sovereign +888 Numbers Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>📱 Выдача анонимных номеров +888 (Fragment Sovereign):</b>"_q,
			st::boxLabel));

		const auto phoneInput = box->addRow(object_ptr<Ui::InputField>(
			box,
			st::defaultInputField,
			rpl::single(u"+888 XXXX XXXX"_q),
			u"+888 0001 0001"_q));

		// Preset buttons for +888 numbers
		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"Пресет: +888 0001 0001 (Genesis #1)"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			phoneInput->setText(u"+888 0001 0001"_q);
		});

		box->addSkip(3);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"Пресет: +888 7777 7777 (Lucky Sevens)"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			phoneInput->setText(u"+888 7777 7777"_q);
		});

		box->addSkip(8);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"📱 Закрепить номер за аккаунтом Создателя"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			const auto rawNumber = phoneInput->getLastText().trimmed();
			const auto user = controller->session().user();
			user->setPhone(rawNumber);
			controller->uiShow()->showToast(
				u"👑 Номер "_q + rawNumber + u" успешно привязан к аккаунту Создателя!"_q);
		});

		box->addSkip(12);

		// --- Stealth & Security Toggles ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>Шпионские и защитные модули (Sovereign Security):</b>"_q,
			st::boxLabel));

		box->addRow(object_ptr<Ui::Checkbox>(
			box,
			u"👻 Ghost Mode (Невидимка: чтение без галочек, скрытие набора текста)"_q,
			GhostModeEnabled,
			st::defaultCheckbox));

		box->addRow(object_ptr<Ui::Checkbox>(
			box,
			u"🗑️ Anti-Delete (Сохранять удаленные сообщения навсегда)"_q,
			AntiDeleteEnabled,
			st::defaultCheckbox));

		box->addSkip(12);

		// --- Minting Section ---
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"<b>Мастер-минт подарков и редких юзернеймов:</b>"_q,
			st::boxLabel));

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"🎁 Чеканить любой подарок / NFT с номером #0001"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"🎁 Подарок #0001 отчеканен и добавлен в инвентарь!"_q);
		});

		box->addSkip(3);

		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"⭐ Зачислить 999,999,999 Telegram Stars"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"⭐ 999,999,999 Stars начислены Создателю!"_q);
		});

		box->addSkip(15);

		// --- Save / Close ---
		box->addButton(rpl::single(u"Сохранить и применить"_q), [=] {
			box->closeBox();
			controller->uiShow()->showToast(u"⚡ Настройки NovexGram Sovereign применены!"_q);
		});
	}));
}

} // namespace NovexGram
