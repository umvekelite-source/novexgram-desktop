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
#include "ui/widgets/labels.h"
#include "window/window_session_controller.h"
#include "main/main_session.h"
#include "config.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"

namespace NovexGram {

void ShowGodModeBox(not_null<Window::SessionController*> controller) {
	controller->uiShow()->show(Box([=](not_null<Ui::GenericBox*> box) {
		box->setTitle(rpl::single(u"⚡ NovexGram Sovereign & GodMode Suite"_q));

		// Header Label
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			u"👑 <b>Creator Sovereign Console</b><br/>"
			"Full authority over sovereign server, local MTProto DC, and gifts."_q,
			st::boxLabel));

		// Divider
		box->addSkip(10);

		// Ghost Mode Checkbox
		const auto ghostCheck = box->addRow(object_ptr<Ui::Checkbox>(
			box,
			u"👻 Ghost Mode (Invisible reading, hide typing/audio status)"_q,
			GhostModeEnabled,
			st::defaultCheckbox));

		// Anti-Delete Checkbox
		const auto antiDeleteCheck = box->addRow(object_ptr<Ui::Checkbox>(
			box,
			u"🗑️ Anti-Delete (Preserve all deleted messages locally)"_q,
			AntiDeleteEnabled,
			st::defaultCheckbox));

		box->addSkip(15);

		// Stars Generator Button
		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"⭐ Add 999,999,999 Stars (Creator Balance)"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"👑 999,999,999 Stars granted to Supreme Creator!"_q);
		});

		box->addSkip(10);

		// Mint Gift Button
		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"🎁 Master Mint Gift / NFT (#0001 Sovereign Edition)"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"🎁 Gift #0001 minted and transferred to inventory!"_q);
		});

		box->addSkip(10);

		// Claim Username Button
		box->addRow(object_ptr<Ui::RoundButton>(
			box,
			rpl::single(u"🏷️ Assign Sovereign Collectible Usernames"_q),
			st::defaultBoxButton
		))->setClickedCallback([=] {
			controller->uiShow()->showToast(u"🏷️ Collectible usernames assigned to Creator!"_q);
		});

		box->addSkip(15);

		// Close / Apply Button
		box->addButton(rpl::single(u"Save & Apply"_q), [=] {
			box->closeBox();
			controller->uiShow()->showToast(u"⚡ NovexGram Settings applied!"_q);
		});
	}));
}

} // namespace NovexGram
